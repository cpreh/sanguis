#include "unpaused.hpp"
#include "../entities/player.hpp"
#include "../message_functor.hpp"
#include "../../truncation_check_cast.hpp"
#include "../../dispatch_type.hpp"
#include "../../messages/level_change.hpp"
#include "../../messages/client_info.hpp"
#include "../../messages/disconnect.hpp"
#include "../../messages/player_rotation.hpp"
#include "../../messages/player_start_shooting.hpp"
#include "../../messages/player_stop_shooting.hpp"
#include "../../messages/player_change_weapon.hpp"
#include "../../messages/player_direction.hpp"
#include "../../messages/game_state.hpp"
#include "../../messages/add_weapon.hpp"
#include "../../messages/change_weapon.hpp"
#include "../../messages/experience.hpp"
#include "../message_converter.hpp"
#include "../damage_types.hpp"
#include "../../resolution.hpp"
#include "../weapons/factory.hpp"
#include "../../angle_vector.hpp"
#include "../entities/zombie.hpp"
#include "../entities/entity.hpp"

#include <sge/math/random.hpp>
#include <sge/math/constants.hpp>
#include <sge/math/angle.hpp>
#include <sge/iostream.hpp>

#include <boost/mpl/vector.hpp>
#include <boost/bind.hpp>
#include <boost/assign/list_of.hpp>

sanguis::server::states::unpaused::unpaused()
	: send_timer(SGE_TEXT("send_timer"),sge::su(0.1))
{}

void sanguis::server::states::unpaused::level_callback(entities::player &p,const messages::level_type)
{
	// no message_converter here because it operates on a _specific_ entity type
	context<running>().send(new messages::level_change(p.id(),p.level()));
}

boost::statechart::result sanguis::server::states::unpaused::handle_default_msg(const net::id_type id,const messages::base &m)
{
	sge::clog << SGE_TEXT("server: received unexpected message from id ") << id << SGE_TEXT(" of type ") << typeid(m).name() << SGE_TEXT("\n");
	return discard_event();
}

void sanguis::server::states::unpaused::create_game(const net::id_type net_id,const messages::client_info &m)
{
	assert(!context<running>().entities().size());

	sge::clog << SGE_TEXT("server: sending game messages\n");

	context<running>().send(new messages::game_state(game_state(truncation_check_cast<game_state::score_type>(0))));

	entities::entity &raw_player = context<running>().insert_entity(
		entities::auto_ptr(
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
					(entities::property::type::health,entities::property(messages::mu(100)))
					(entities::property::type::movement_speed,entities::property(messages::mu(0),messages::mu(100))),

				m.name())));
	
	entities::player &p = dynamic_cast<entities::player &>(raw_player);
	
	context<running>().players()[net_id] = &p;

	p.add_weapon(weapons::create(weapon_type::melee,get_environment()));
	context<running>().send(new messages::add_weapon(p.id(),weapon_type::melee));
	p.add_weapon(weapons::create(weapon_type::pistol,get_environment()));
	context<running>().send(new messages::add_weapon(p.id(),weapon_type::pistol));

	// send start experience
	// no message_converter here because it operates on a _specific_ entity type
	context<running>().send(new messages::experience(p.id(),p.exp()));
	context<running>().send(new messages::level_change(p.id(),p.level()));

	context<running>().enemy_timer().reset();
}

boost::statechart::result sanguis::server::states::unpaused::operator()(const net::id_type id,const messages::player_change_weapon &e)
{
	const running::player_map::iterator it(context<running>().players().find(id));
	if (it == context<running>().players().end())
	{
		sge::clog << SGE_TEXT("server: got player_change_weapon from spectator ") << id << SGE_TEXT('\n');
		return discard_event();
	}
	entities::player &player_(*it->second);

	if (e.weapon() > weapon_type::size)
		throw sge::exception("got invalid weapon type in player_change_weapon");

	const weapon_type::type type(static_cast<weapon_type::type>(e.weapon()));

	player_.change_weapon(type);

	context<running>().send(new messages::change_weapon(player_.id(), e.weapon()));
	return discard_event();
}

boost::statechart::result sanguis::server::states::unpaused::operator()(const net::id_type id,const messages::player_rotation &e)
{
	const running::player_map::iterator it(context<running>().players().find(id));
	if (it == context<running>().players().end())
	{
		sge::clog << SGE_TEXT("server: got rotation_event from spectator ") << id << SGE_TEXT('\n');
		return discard_event();
	}

	entities::player &player_(*it->second);

	// FIXME: we should really transport the target point over the network
	player_.target(
		player_.pos()
		+ angle_to_vector(player_.direction()) * 100);

	player_.angle(e.angle());
	context<running>().send(message_convert<messages::rotate>(player_));
	return discard_event();
}

void sanguis::server::states::unpaused::add_enemy()
{
	const messages::space_unit rand_angle = sge::math::random(messages::mu(0),
					messages::mu(2)*sge::math::pi<messages::space_unit>());
	const messages::space_unit radius = messages::mu(std::max(resolution().w(),resolution().h()))/messages::mu(2);
	const messages::space_unit scale = messages::mu(1.5);

	const messages::pos_type screen_center = messages::pos_type(messages::mu(resolution().w()),messages::mu(resolution().h()))/messages::mu(2);
	const messages::pos_type center = scale * radius * angle_to_vector(rand_angle);
	
	// TODO: take the nearest player here instead of the first
	//boost::optional<messages::space_unit> oa = sge::math::angle_to<messages::space_unit>(context<running>().players().begin()->second->center() - center);
	//const messages::space_unit angle = oa ? *oa : messages::mu(0);
	const messages::pos_type pos = center + screen_center;
	const messages::space_unit angle = messages::mu(0);

	context<running>().insert_entity(
		entities::auto_ptr(
			new entities::zombie(
				get_environment(),
				(
					damage::all=messages::mu(0)
				),
				pos,
				angle, // angle and direction (are the same here)
				angle,
				
				boost::assign::map_list_of
					(entities::property::type::health,entities::property(messages::mu(3)))
					(entities::property::type::movement_speed,entities::property(messages::mu(50)))
				)));
}

boost::statechart::result sanguis::server::states::unpaused::operator()(const net::id_type id,const messages::player_start_shooting &)
{
	if (context<running>().players().find(id) == context<running>().players().end())
	{
		sge::clog << SGE_TEXT("server: got shooting event from spectator ") << id << SGE_TEXT("\n");
		return discard_event();
	}

	context<running>().players()[id]->aggressive(true);
	return discard_event();
}

boost::statechart::result sanguis::server::states::unpaused::operator()(const net::id_type id,const messages::player_stop_shooting &)
{
	if (context<running>().players().find(id) == context<running>().players().end())
	{
		sge::clog << SGE_TEXT("server: got player_stop_shooting from spectator ") << id << SGE_TEXT("\n");
		return discard_event();
	}

	context<running>().players()[id]->aggressive(false);
	return discard_event();
}

boost::statechart::result sanguis::server::states::unpaused::operator()(const net::id_type id,const messages::player_direction &e)
{
	const running::player_map::iterator it(context<running>().players().find(id));
	if (it == context<running>().players().end())
	{
		sge::clog << SGE_TEXT("server: got direction_event from spectator ") << id << SGE_TEXT("\n");
		return discard_event();
	}

	entities::player &player_(*it->second);

	if (e.dir().is_null())
	{
		player_.get_property(entities::property::type::movement_speed).current(messages::mu(0));
	}
	else
	{
		player_.get_property(entities::property::type::movement_speed).set_current_to_max();
		player_.direction(*sge::math::angle_to<messages::space_unit>(e.dir()));
	}

	context<running>().send(message_convert<messages::speed>(player_));
	return discard_event();
}

boost::statechart::result sanguis::server::states::unpaused::operator()(const net::id_type id,const messages::client_info&m) 
{
	sge::clog << SGE_TEXT("server: received client info from ") << id << SGE_TEXT("\n");
	create_game(id,m);
	return discard_event();
}

boost::statechart::result sanguis::server::states::unpaused::operator()(const net::id_type id,const messages::disconnect&) 
{
	if (context<running>().players().find(id) == context<running>().players().end())
	{
		sge::clog << SGE_TEXT("server: spectator ") << id << SGE_TEXT(" disconnected\n");
		return discard_event();
	}

	sge::clog << SGE_TEXT("server: disconnected\n");
	return discard_event();
}

void sanguis::server::states::unpaused::divide_exp(const messages::exp_type exp)
{
	if (exp == static_cast<messages::exp_type>(0))
		return;

	for (running::player_map::iterator i = context<running>().players().begin(); i != context<running>().players().end(); ++i)
	{
		entities::player &p = *(i->second);
		p.exp(p.exp()+exp);
		context<running>().send(new messages::experience(p.id(),p.exp()));
	}
}

void sanguis::server::states::unpaused::get_player_exp(const sge::con::arg_list &)
{
	context<running>().console_print(
		SGE_TEXT("player experience is: ")+
			boost::lexical_cast<sge::string>(
				context<running>().players().begin()->second->exp()));
}

sanguis::server::environment sanguis::server::states::unpaused::get_environment()
{
	return environment(
		context<running>().send,
		boost::bind(&running::insert_entity,&context<running>(),_1),
		boost::bind(&unpaused::divide_exp,this,_1),
		boost::bind(&unpaused::level_callback,this,_1,_2));
}

boost::statechart::result sanguis::server::states::unpaused::react(const tick_event &t)
{
	const time_type delta = t.delta();

	if (context<running>().enemy_timer().update_b())
		add_enemy();

	// should we send position updates?
	const bool update_pos = send_timer.v().update_b();

	entities::container &entities = context<running>().entities();

	for (entities::container::iterator i = entities.begin(); i != entities.end();)
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
					context<running>().send(message_convert<messages::health>(*i));
					context<running>().send(message_convert<messages::remove>(*i));
				}
				i = entities.erase(i);
				continue;
			}
		}

		i->update(
			static_cast<entities::entity::time_type>(delta),
			entities);

		if (i->type() != entity_type::indeterminate && update_pos)
		{
			context<running>().send(message_convert<messages::move>(*i));
			context<running>().send(message_convert<messages::speed>(*i));
			context<running>().send(message_convert<messages::rotate>(*i));
			context<running>().send(message_convert<messages::health>(*i)); // FIXME: this should be elsewhere
		}

		++i;
	}
	return discard_event();
}

boost::statechart::result sanguis::server::states::unpaused::react(const message_event &m)
{
	message_functor<unpaused,boost::statechart::result> mf(*this,m.id);

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
		boost::statechart::result>(
			mf,
			*m.message,
			boost::bind(&unpaused::handle_default_msg, this, m.id, _1));
}
