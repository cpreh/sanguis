#include "../messages/client_info.hpp"
#include "../messages/player_direction.hpp"
#include "../messages/player_rotation.hpp"
#include "../messages/player_start_shooting.hpp"
#include "../messages/player_stop_shooting.hpp"
#include "../messages/disconnect.hpp"
#include "../messages/player_change_weapon.hpp"
#include "../messages/change_weapon.hpp"
#include "../messages/game_state.hpp"
#include "../truncation_check_cast.hpp"
#include "../game_state.hpp"
#include "../dispatch_type.hpp"
#include "../angle_vector.hpp"
#include "../resolution.hpp"
#include "message_functor.hpp"
#include "game_logic.hpp"
#include "player.hpp"
#include "converter.hpp"
#include "zombie.hpp"

#include <sge/iostream.hpp>
#include <sge/math/random.hpp>
#include <sge/math/constants.hpp>
#include <sge/math/angle.hpp>

#include <boost/mpl/vector.hpp>
#include <boost/bind.hpp>

sanguis::server::game_logic::game_logic(send_callback send) 
	: send(send),
	  aborted_(false),
	  send_timer(SGE_TEXT("message_freq"),sge::su(0.1)),
		enemy_timer(SGE_TEXT("enemy_timer"),sge::su(2))
{}

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
			if (i->type() == entity_type::player)
			{
				sge::cout << "server: player's dead!\n";
			}
			else
			{
				send(message_convert<messages::remove>(*i));
				i = entities.erase(i);
				continue;
			}
		}

		i->update(static_cast<entity::time_type>(delta));

		if (update_pos)
		{
			send(message_convert<messages::move>(*i));
			send(message_convert<messages::speed>(*i));
			send(message_convert<messages::rotate>(*i));
		}

		++i;
	}
}

void sanguis::server::game_logic::create_game(const net::id_type net_id,const messages::client_info &m)
{
	assert(!entities.size());

	entity &raw_player = insert_entity(new server::player(
			net_id,
			messages::pos_type(
				messages::mu(resolution().w()/2),
				messages::mu(resolution().h()/2)),
			messages::mu(0),
			messages::mu(0),
			messages::mu(0),
			messages::mu(100),
			messages::mu(100),
			m.name()));
	
	players[net_id] = &dynamic_cast<player &>(raw_player);

	sge::clog << SGE_TEXT("server: sending game messages\n");

	send(new messages::game_state(game_state(truncation_check_cast<game_state::score_type>(0))));
	send(message_convert<messages::add>(*players[net_id]));

	enemy_timer.v().reset();
}

void sanguis::server::game_logic::operator()(const net::id_type id,const messages::player_change_weapon &e)
{
	// TODO: check if the player _has_ this weapon before assigning it
	send(new messages::change_weapon(players[id]->id(),e.weapon()));
}

void sanguis::server::game_logic::operator()(const net::id_type id,const messages::player_rotation &e)
{
	if (players.find(id) == players.end())
	{
		sge::clog << SGE_TEXT("server: got rotation_event from spectator ") << id << SGE_TEXT("\n");
		return;
	}

	players[id]->angle(e.angle());
	send(message_convert<messages::rotate>(*players[id]));
}

sanguis::server::entity &sanguis::server::game_logic::insert_entity(entity *ptr)
{
	entities.push_back(ptr);
	return entities.back();
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
	boost::optional<messages::space_unit> oa = sge::math::angle_to<messages::space_unit>(players.begin()->second->center() - center);
	const messages::space_unit angle = oa ? *oa : messages::mu(0);

	const messages::pos_type pos = center + screen_center;

	zombie &b = dynamic_cast<zombie &>(
		insert_entity(new zombie(pos,angle,messages::mu(1),angle,messages::mu(50),messages::mu(50))));

	send(message_convert<messages::add>(b));
}

void sanguis::server::game_logic::operator()(const net::id_type id,const messages::player_start_shooting &)
{
	if (players.find(id) == players.end())
	{
		sge::clog << SGE_TEXT("server: got shooting event from spectator ") << id << SGE_TEXT("\n");
		return;
	}

	players[id]->shooting(true);
}

void sanguis::server::game_logic::operator()(const net::id_type id,const messages::player_stop_shooting &)
{
	if (players.find(id) == players.end())
	{
		sge::clog << SGE_TEXT("server: got player_stop_shooting from spectator ") << id << SGE_TEXT("\n");
		return;
	}

	players[id]->shooting(false);
}

void sanguis::server::game_logic::operator()(const net::id_type id,const messages::player_direction &e)
{
	if (players.find(id) == players.end())
	{
		sge::clog << SGE_TEXT("server: got direction_event from spectator ") << id << SGE_TEXT("\n");
		return;
	}

	if (e.dir().is_null())
	{
		players[id]->speed(messages::mu(0));
	}
	else
	{
		players[id]->speed(messages::mu(1));
		players[id]->direction(*sge::math::angle_to<messages::space_unit>(e.dir()));
	}

	send(message_convert<messages::speed>(*players[id]));
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

#if 0
void sanguis::server::running_state::ai_hook(entity &e,const entity::time_type diff)
{
	switch (e.ai_type())
	{
		case ai_type::none:
			e.pos(e.pos() + e.abs_speed() * diff);
		break;
		case ai_type::simple:
		{
			const messages::pos_type diffvec = (player_->center() - e.center());
			if (!diffvec.is_null())
			{
				const messages::space_unit angle = *sge::math::angle_to<messages::space_unit>(diffvec);
				e.pos(e.pos() + sge::math::normalize(diffvec) * e.max_speed() * diff);
				e.angle(angle);
				e.direction(angle);
			}
		}
		break;
	}
}
#endif
