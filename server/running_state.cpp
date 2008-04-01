#include "running_state.hpp"
#include "waiting_state.hpp"
#include "get_unique_id.hpp"
#include "../messages/player_rotation_event.hpp"
#include "../messages/player_direction_event.hpp"
#include "../messages/player_start_shooting.hpp"
#include "../messages/player_stop_shooting.hpp"
#include "../messages/add.hpp"
#include "../messages/remove.hpp"
#include "../messages/game_state.hpp"
#include "../messages/player_state.hpp"
#include "../messages/client_info.hpp"
#include "../messages/rotate.hpp"
#include "../messages/disconnect.hpp"
#include "../messages/move.hpp"
#include "../messages/speed.hpp"
#include "../entity_type.hpp"
#include "../game_state.hpp"
#include "../dispatch_type.hpp"
#include "../truncation_check_cast.hpp"
#include "../truncation_check_structure_cast.hpp"
#include "message_functor.hpp"

#include <sge/iostream.hpp>
#include <sge/su.hpp>
#include <sge/string.hpp>
#include <sge/math/vector.hpp>
#include <sge/math/rect.hpp>
#include <sge/math/rect_impl.hpp>
#include <sge/math/rect_util.hpp>
#include <sge/math/atan2.hpp>

#include <boost/bind.hpp>
#include <boost/mpl/vector.hpp>

#include <cmath>
#include <cassert>

namespace
{
sge::math::vector2 angle_to_vector(const sge::space_unit angle)
{
	return sge::math::vector2(std::cos(angle),std::sin(angle));
}
}

sanguis::server::running_state::running_state()
	: player_speed(SGE_TEXT("player_speed"),sge::su(0.1)),
	  bullet_speed(SGE_TEXT("bullet_speed"),sge::su(0.4)),
		bullet_freq(SGE_TEXT("bullet_freq"),sge::su(0.25)),
	  send_timer(sge::second()),
		message_freq(SGE_TEXT("message_freq"),
			boost::bind(&running_state::set_message_freq,this,_1,_2),sge::su(0.5))
{
	sge::clog << SGE_TEXT("server: entering running state\n");
}

sge::space_unit sanguis::server::running_state::set_message_freq(const sge::space_unit,const sge::space_unit newv)
{
	send_timer.interval(static_cast<sge::time_type>(static_cast<sge::space_unit>(sge::second())*newv));
	return newv;
}

boost::statechart::result sanguis::server::running_state::react(const tick_event&t) 
{
	const sge::timer::frames_type delta = t.data.diff_time;

	const bool update_pos = send_timer.update_b();

	for (player_map::iterator i = players.begin(); i != players.end(); ++i)
	{
		i->second.pos += i->second.speed * static_cast<messages::space_unit>(delta);

		if (update_pos)
			context<machine>().send(
				new messages::move(i->second.id,i->second.pos));

		if (i->second.shooting && i->second.shoot_timer->update_b())
			add_bullet(i->first);
	}

	bool deletion = false;
	for (bullet_map::iterator i = bullets.begin(); i != bullets.end(); ++i)
	{
		if (deletion)
		{
			--i;
			deletion = false;
		}

		i->second.pos += i->second.speed * static_cast<messages::space_unit>(delta);

		// bullet not visible anymore?
		if (!sge::math::intersects(
			sge::math::rect(sge::su(-0.5),sge::su(-0.5),sge::su(1.5),sge::su(1.5)),
			i->second.pos))
		{
			context<machine>().send(new messages::remove(i->first));
			bullet_map::iterator d = i++;
			bullets.erase(d);
			deletion = true;

			if (i == bullets.end())
				break;
		}
	}

	return discard_event();
}

void sanguis::server::running_state::create_game(const net::id_type id,const messages::client_info &m)
{
	assert(!players.size());

	/*
	player p(get_unique_id(),m.name(),bullet_freq.value(),
		messages::pos_type(static_cast<messages::space_unit>(0.5),static_cast<messages::space_unit>(0.5)));
	*/

	player_type &player = players[id];

	player.id =     get_unique_id();
	player.name =   m.name();
	player.shooting = false;
	player.shoot_timer.reset(new sge::timer(static_cast<sge::timer::interval_type>(sge::su(sge::second())*bullet_freq.value())));
	player.pos =    messages::pos_type(static_cast<messages::space_unit>(0.5),static_cast<messages::space_unit>(0.5));
	player.angle =  static_cast<messages::space_unit>(0);
	player.health = static_cast<messages::space_unit>(1);

	// send player entity, game state and player state
	sge::clog << SGE_TEXT("server: sending game messages\n");
	context<machine>().send(new messages::game_state(game_state(truncation_check_cast<boost::uint32_t>(0))));
	context<machine>().send(
		new messages::add(player.id,
			entity_type::player,
			player.pos,
			player.angle,
			messages::vector2(),
			static_cast<messages::space_unit>(1)));
	context<machine>().send(new messages::player_state(player.id,player_state(weapon_type::pistol,truncation_check_cast<boost::uint32_t>(0))));
}

boost::statechart::result sanguis::server::running_state::operator()(const net::id_type id,const messages::player_rotation_event &e)
{
	if (players.find(id) == players.end())
	{
		sge::clog << SGE_TEXT("server: got rotation_event from spectator ") << id << SGE_TEXT("\n");
		return discard_event();
	}

	player_type &player = players[id];
	player.angle = e.angle();
	context<machine>().send(new messages::rotate(player.id,player.angle));
	return discard_event();
}

void sanguis::server::running_state::add_bullet(const net::id_type id)
{
	const entity_id bullet_id = get_unique_id();
	bullet_type &b = bullets[bullet_id] = bullet_type(players[id].pos, angle_to_vector(players[id].angle) * bullet_speed.value());

	context<machine>().send(
		new messages::add(bullet_id,entity_type::bullet,b.pos,players[id].angle,b.speed));
}

boost::statechart::result sanguis::server::running_state::operator()(const net::id_type id,const messages::player_start_shooting &)
{
	if (players.find(id) == players.end())
	{
		sge::clog << SGE_TEXT("server: got shooting event from spectator ") << id << SGE_TEXT("\n");
		return discard_event();
	}

	players[id].shooting = true;
	add_bullet(id);
	return discard_event();
}

boost::statechart::result sanguis::server::running_state::operator()(const net::id_type id,const messages::player_stop_shooting &)
{
	if (players.find(id) == players.end())
		return discard_event();

	players[id].shooting = false;
	return discard_event();
}

boost::statechart::result sanguis::server::running_state::operator()(const net::id_type id,const messages::player_direction_event &e)
{
	if (players.find(id) == players.end())
	{
		sge::clog << SGE_TEXT("server: got direction_event from spectator ") << id << SGE_TEXT("\n");
		return discard_event();
	}

	player_type &player = players[id];

	if (e.dir().is_null())
		player.speed = sge::math::vector2();
	else
		player.speed = sge::math::normalize(e.dir()) * player_speed.value();

	context<machine>().send(new messages::speed(player.id,player.speed));
	return discard_event();
}

boost::statechart::result sanguis::server::running_state::operator()(const net::id_type id,const messages::client_info&m) 
{
	if (players.size())
	{
		sge::clog << SGE_TEXT("server: got superfluous client info from id ") << id << SGE_TEXT("\n");
		return discard_event();
	}
	sge::clog << SGE_TEXT("server: received client info from ") << id << SGE_TEXT("\n");
	create_game(id,m);
	return discard_event();
}

boost::statechart::result sanguis::server::running_state::operator()(const net::id_type id,const messages::disconnect&) 
{
	if (players.find(id) == players.end())
	{
		sge::clog << SGE_TEXT("spectator ") << id << SGE_TEXT(" disconnected\n");
		return discard_event();
	}
	sge::clog << SGE_TEXT("server: disconnected\n");
	return transit<waiting_state>();
}

boost::statechart::result sanguis::server::running_state::handle_default_msg(const net::id_type id,const messages::base&m) 
{
	sge::clog << SGE_TEXT("server: received unexpected message ") << typeid(m).name() << SGE_TEXT(" from id ") << id << SGE_TEXT("\n");
	return discard_event();
}

boost::statechart::result sanguis::server::running_state::react(const message_event&m) 
{
	message_functor<running_state> mf(*this,m.id);

	return dispatch_type<
		boost::mpl::vector<
			messages::disconnect,
			messages::client_info,
			messages::player_rotation_event,
			messages::player_start_shooting,
			messages::player_stop_shooting,
			messages::player_direction_event
		>,
		boost::statechart::result>(
		mf,
		*m.message,
		boost::bind(&running_state::handle_default_msg, this, m.id, _1));
}
