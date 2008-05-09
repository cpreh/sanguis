#include "../messages/client_info.hpp"
#include "../messages/player_direction.hpp"
#include "../messages/player_rotation.hpp"
#include "../messages/player_start_shooting.hpp"
#include "../messages/player_stop_shooting.hpp"
#include "../messages/disconnect.hpp"
#include "../messages/add_weapon.hpp"
#include "../messages/player_change_weapon.hpp"
#include "../messages/change_weapon.hpp"
#include "../messages/level_change.hpp"
#include "../messages/game_state.hpp"
#include "../messages/experience.hpp"
#include "../truncation_check_cast.hpp"
#include "../game_state.hpp"
#include "../dispatch_type.hpp"
#include "../angle_vector.hpp"
#include "../resolution.hpp"
#include "message_functor.hpp"
#include "game_logic.hpp"
#include "damage_types.hpp"
#include "collision.hpp"
#include "message_converter.hpp"
#include "entities/player.hpp"
#include "entities/zombie.hpp"
#include "weapons/factory.hpp"

#include <sge/iostream.hpp>
#include <sge/math/random.hpp>
#include <sge/math/constants.hpp>
#include <sge/math/angle.hpp>

#include <boost/mpl/vector.hpp>
#include <boost/bind.hpp>
#include <boost/assign/list_of.hpp>

sanguis::server::game_logic::game_logic(
	const send_callback send,
	const console_print_callback console_print) 
	: send(send),
		console_print(console_print),
	  aborted_(false),
	  send_timer(SGE_TEXT("message_freq"),sge::su(0.1)),
		enemy_timer(SGE_TEXT("enemy_timer"),sge::su(2))
{
	sge::con::add(SGE_TEXT("player_exp"),boost::bind(&game_logic::get_player_exp,this,_1));
}

void sanguis::server::game_logic::level_callback(entities::player &p,const messages::level_type)
{
	// no message_converter here because it operates on a _specific_ entity type
	send(new messages::level_change(p.id(),p.level()));
}

void sanguis::server::game_logic::process(const net::id_type id,const messages::base &m)
{
	message_functor<game_logic,void> mf(*this,id);

	return dispatch_type<
		boost::mpl::vector<
			messages::disconnect,
			messages::client_info,
			messages::player_rotation,
			messages::player_start_shooting,
			messages::player_stop_shooting,
			messages::player_change_weapon,
			messages::player_direction
		>,
		void>(
		mf,
		m,
		boost::bind(&game_logic::handle_default_msg, this, id, _1));
}

void sanguis::server::game_logic::handle_default_msg(const net::id_type id,const messages::base &m)
{
	sge::clog << SGE_TEXT("server: received unexpected message from id ") << id << SGE_TEXT(" of type ") << typeid(m).name() << SGE_TEXT("\n");
}

void sanguis::server::game_logic::update(const time_type delta)
{
	if (enemy_timer.v().update_b())
		add_enemy();

	// should we send position updates?
	const bool update_pos = send_timer.v().update_b();

	for (entity_container::iterator i = entities.begin(); i != entities.end();)
	{
		if (i->dead())
		{
			/*if (i->type() == entity_type::player)
			{
				sge::cout << "server: player's dead!\n";
			}
			else*/
			{
				if(i->type() != entity_type::indeterminate)
				{
					send(message_convert<messages::health>(*i));
					send(message_convert<messages::remove>(*i));
				}
				i = entities.erase(i);
				continue;
			}
		}

		i->update(
			static_cast<entity::time_type>(delta),
			entities);

		if (i->type() != entity_type::indeterminate && update_pos)
		{
			send(message_convert<messages::move>(*i));
			send(message_convert<messages::speed>(*i));
			send(message_convert<messages::rotate>(*i));

			send(message_convert<messages::health>(*i)); // FIXME: this should be elsewhere
		}

		++i;
	}
}

void sanguis::server::game_logic::create_game(const net::id_type net_id,const messages::client_info &m)
{
	assert(!entities.size());

	sge::clog << SGE_TEXT("server: sending game messages\n");

	send(new messages::game_state(game_state(truncation_check_cast<game_state::score_type>(0))));

	entity &raw_player = insert_entity(
		entity_ptr(
			new entities::player(
				get_environment(),
				(
					damage::all=messages::mu(0)
				),
				net_id,
				messages::pos_type(
					messages::mu(resolution().w()/2),
					messages::mu(resolution().h()/2)),
				messages::mu(0),
				messages::mu(0),
				
				boost::assign::map_list_of
					(entity::property::type::health, entity::property(messages::mu(100)))
					(entity::property::type::movement_speed, entity::property(messages::mu(0), messages::mu(100))),

				m.name())));
	
	entities::player &p = dynamic_cast<entities::player &>(raw_player);
	
	players[net_id] = &p;

	p.add_weapon(weapons::create(weapon_type::melee,get_environment()));
	send(new messages::add_weapon(p.id(),weapon_type::melee));
	p.add_weapon(weapons::create(weapon_type::pistol,get_environment()));
	send(new messages::add_weapon(p.id(),weapon_type::pistol));

	// send start experience
	// no message_converter here because it operates on a _specific_ entity type
	send(new messages::experience(p.id(),p.exp()));
	send(new messages::level_change(p.id(),p.level()));

	enemy_timer.v().reset();
}

void sanguis::server::game_logic::operator()(const net::id_type id,const messages::player_change_weapon &e)
{
	const player_map::iterator it(players.find(id));
	if (it == players.end())
	{
		sge::clog << SGE_TEXT("server: got player_change_weapon from spectator ") << id << SGE_TEXT('\n');
		return;
	}
	entities::player &player_(*it->second);

	if (e.weapon() > weapon_type::size)
		throw sge::exception("got invalid weapon type in player_change_weapon");

	const weapon_type::type type(static_cast<weapon_type::type>(e.weapon()));

	player_.change_weapon(type);
	/*
	if(type != weapon_type::none)
		player_.change_weapon(
			weapons::create(
				type,
				get_send_callback(),
				get_insert_callback()));
	*/

	send(new messages::change_weapon(player_.id(), e.weapon()));
}

void sanguis::server::game_logic::operator()(const net::id_type id,const messages::player_rotation &e)
{
	const player_map::iterator it(players.find(id));
	if (it == players.end())
	{
		sge::clog << SGE_TEXT("server: got rotation_event from spectator ") << id << SGE_TEXT('\n');
		return;
	}

	entities::player &player_(*it->second);

	// FIXME: we should really transport the target point over the network
	player_.target(
		player_.pos()
		+ angle_to_vector(player_.direction()) * 100);

	player_.angle(e.angle());
	send(message_convert<messages::rotate>(player_));
}

sanguis::server::entity &sanguis::server::game_logic::insert_entity(entity_ptr e)
{
	entities.push_back(e);
	entity &ref = entities.back();
	ref.update(time_type(),entities);

	if (ref.type() != entity_type::indeterminate)
		send(message_convert<messages::add>(ref));
	return ref;
}

bool sanguis::server::game_logic::aborted() const
{
	return aborted_;
}

void sanguis::server::game_logic::add_enemy()
{
	const messages::space_unit rand_angle = sge::math::random(messages::mu(0),
					messages::mu(2)*sge::math::pi<messages::space_unit>());
	const messages::space_unit radius = messages::mu(std::max(resolution().w(),resolution().h()))/messages::mu(2);
	const messages::space_unit scale = messages::mu(1.5);

	const messages::pos_type screen_center = messages::pos_type(messages::mu(resolution().w()),messages::mu(resolution().h()))/messages::mu(2);
	const messages::pos_type center = scale * radius * angle_to_vector(rand_angle);
	
	// TODO: take the nearest player here instead of the first
	//boost::optional<messages::space_unit> oa = sge::math::angle_to<messages::space_unit>(players.begin()->second->center() - center);
	//const messages::space_unit angle = oa ? *oa : messages::mu(0);
	const messages::pos_type pos = center + screen_center;
	const messages::space_unit angle = messages::mu(0);

	insert_entity(
		entity_ptr(
			new entities::zombie(
				get_environment(),
				(
					damage::all=messages::mu(0)
				),
				pos,
				angle, // angle and direction (are the same here)
				angle,
				
				boost::assign::map_list_of
					(entity::property::type::health, entity::property(messages::mu(3)))
					(entity::property::type::movement_speed, entity::property(messages::mu(50)))

				)));
}

void sanguis::server::game_logic::operator()(const net::id_type id,const messages::player_start_shooting &)
{
	if (players.find(id) == players.end())
	{
		sge::clog << SGE_TEXT("server: got shooting event from spectator ") << id << SGE_TEXT("\n");
		return;
	}

	players[id]->aggressive(true);
}

void sanguis::server::game_logic::operator()(const net::id_type id,const messages::player_stop_shooting &)
{
	if (players.find(id) == players.end())
	{
		sge::clog << SGE_TEXT("server: got player_stop_shooting from spectator ") << id << SGE_TEXT("\n");
		return;
	}

	players[id]->aggressive(false);
}

void sanguis::server::game_logic::operator()(const net::id_type id,const messages::player_direction &e)
{
	const player_map::iterator it(players.find(id));
	if (it == players.end())
	{
		sge::clog << SGE_TEXT("server: got direction_event from spectator ") << id << SGE_TEXT("\n");
		return;
	}

	entities::player &player_(*it->second);

	if (e.dir().is_null())
	{
		player_.get_property(entity::property::type::movement_speed).current(messages::mu(0));
	}
	else
	{
		player_.get_property(entity::property::type::movement_speed).set_current_to_max();
		player_.direction(*sge::math::angle_to<messages::space_unit>(e.dir()));
	}

	send(message_convert<messages::speed>(player_));
}

void sanguis::server::game_logic::operator()(const net::id_type id,const messages::client_info&m) 
{
	sge::clog << SGE_TEXT("server: received client info from ") << id << SGE_TEXT("\n");
	create_game(id,m);
}

void sanguis::server::game_logic::operator()(const net::id_type id,const messages::disconnect&) 
{
	if (players.find(id) == players.end())
	{
		sge::clog << SGE_TEXT("server: spectator ") << id << SGE_TEXT(" disconnected\n");
		return;
	}

	sge::clog << SGE_TEXT("server: disconnected\n");
	aborted_ = true;
}

sanguis::server::environment sanguis::server::game_logic::get_environment()
{
	return environment(
		send,
		boost::bind(
			&game_logic::insert_entity,
			this,
			_1),
		boost::bind(
			&game_logic::divide_exp,
			this,
			_1),
		boost::bind(
			&game_logic::level_callback,
			this,
			_1,_2));
}

void sanguis::server::game_logic::divide_exp(const messages::exp_type exp)
{
	if (exp == static_cast<messages::exp_type>(0))
		return;

	for (player_map::iterator i = players.begin(); i != players.end(); ++i)
	{
		entities::player &p = *(i->second);
		p.exp(p.exp()+exp);
		send(new messages::experience(p.id(),p.exp()));
	}
}

void sanguis::server::game_logic::get_player_exp(const sge::con::arg_list &)
{
	console_print(SGE_TEXT("player experience is: ")+boost::lexical_cast<sge::string>(players.begin()->second->exp()));
}
