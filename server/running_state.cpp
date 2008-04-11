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
#include "../resolution.hpp"
#include "../truncation_check_structure_cast.hpp"
#include "../angle_vector.hpp"
#include "message_functor.hpp"
#include "player.hpp"
#include "bullet.hpp"
#include "converter.hpp"

#include <sge/iostream.hpp>
#include <sge/su.hpp>
#include <sge/string.hpp>
#include <sge/math/vector.hpp>
#include <sge/math/rect.hpp>
#include <sge/math/rect_impl.hpp>
#include <sge/math/rect_util.hpp>
#include <sge/math/angle.hpp>

#include <boost/bind.hpp>
#include <boost/mpl/vector.hpp>

#include <cmath>
#include <cassert>


sanguis::server::running_state::running_state()
	: send_timer(SGE_TEXT("message_freq"),sge::su(0.5)),
		enemy_timer(SGE_TEXT("enemy_timer"),sge::su(20))
{
	sge::clog << SGE_TEXT("server: entering running state\n");
}

void sanguis::server::running_state::ai_hook(entity &e,const entity::time_type diff)
{
	//if (e.ai_type() == ai_type::none)
		e.pos(e.pos() + e.abs_speed() * diff);
	
}

boost::statechart::result sanguis::server::running_state::react(const tick_event&t) 
{
	const sge::timer::frames_type delta = t.data.diff_time;

	const bool update_pos = send_timer.v().update_b();

	bool deletion = false;
	for (entity_map::iterator i = entities.begin(); i != entities.end(); ++i)
	{
		if (deletion)
		{
			--i;
			deletion = false;
		}

		ai_hook(*(i->second),delta);
		//i->second->update(delta);

		if (i->second->type() == entity_type::player && dynamic_cast<server::player &>(*i->second).spawn_bullet())
			add_bullet();

		if (i->second->type() == entity_type::bullet && !dynamic_cast<server::bullet &>(*i->second).visible())
		{
			context<machine>().send(message_convert<messages::remove>(*i->second));
			entity_map::iterator d = i++;
			entities.erase(d);
			deletion = true;

			if (i == entities.end())
				break;
		}

		if (update_pos && i->second->type() != entity_type::bullet)
			context<machine>().send(message_convert<messages::move>(*i->second));
	}

	return discard_event();
}

void sanguis::server::running_state::create_game(const net::id_type net_id,const messages::client_info &m)
{
	assert(!entities.size());

	const entity_id player_id = get_unique_id();

	entity &raw_player = insert_entity(player_id,
		new server::player(
			player_id,
			net_id,
			messages::pos_type(
				static_cast<messages::space_unit>(resolution().w()/2),
				static_cast<messages::space_unit>(resolution().h()/2)),
			static_cast<messages::space_unit>(0),
			static_cast<messages::space_unit>(0),
			static_cast<messages::space_unit>(0),
			static_cast<messages::space_unit>(1),
			static_cast<messages::space_unit>(1),
			m.name()));
	
	player_ = &dynamic_cast<player &>(raw_player);

	sge::clog << SGE_TEXT("server: sending game messages\n");

	context<machine>().send(new messages::game_state(game_state(truncation_check_cast<boost::uint32_t>(0))));
	context<machine>().send(message_convert<messages::add>(*player_));
	context<machine>().send(new messages::player_state(player_->id(),player_state(weapon_type::pistol,truncation_check_cast<boost::uint32_t>(0))));
}

boost::statechart::result sanguis::server::running_state::operator()(const net::id_type id,const messages::player_rotation_event &e)
{
	if (player_->net_id() != id)
	{
		sge::clog << SGE_TEXT("server: got rotation_event from spectator ") << id << SGE_TEXT("\n");
		return discard_event();
	}

	player_->angle(e.angle());
	context<machine>().send(message_convert<messages::rotate>(*player_));
	return discard_event();
}

sanguis::server::entity &sanguis::server::running_state::insert_entity(const entity_id id,entity *ptr)
{
	return *(entities.insert(id,entity_ptr(ptr)).first->second);
}

void sanguis::server::running_state::add_bullet()
{
	const entity_id bullet_id = get_unique_id();

	bullet &b = dynamic_cast<bullet &>(
		insert_entity(
			bullet_id,
			new bullet(bullet_id,player_->center(),player_->angle(),player_->angle())));

	context<machine>().send(message_convert<messages::add>(b));
}

boost::statechart::result sanguis::server::running_state::operator()(const net::id_type id,const messages::player_start_shooting &)
{
	if (player_->net_id() != id)
	{
		sge::clog << SGE_TEXT("server: got shooting event from spectator ") << id << SGE_TEXT("\n");
		return discard_event();
	}

	player_->shooting(true);
	add_bullet();
	return discard_event();
}

boost::statechart::result sanguis::server::running_state::operator()(const net::id_type id,const messages::player_stop_shooting &)
{
	if (player_->net_id() != id)
		return discard_event();

	player_->shooting(false);
	return discard_event();
}

boost::statechart::result sanguis::server::running_state::operator()(const net::id_type id,const messages::player_direction_event &e)
{
	if (player_->id() != id)
	{
		sge::clog << SGE_TEXT("server: got direction_event from spectator ") << id << SGE_TEXT("\n");
		return discard_event();
	}

	if (e.dir().is_null())
	{
		player_->speed(static_cast<messages::space_unit>(0));
	}
	else
	{
		player_->speed(static_cast<messages::space_unit>(1));
		player_->direction(*sge::math::angle_to<messages::space_unit>(e.dir()));
	}

	context<machine>().send(message_convert<messages::speed>(*player_));
	return discard_event();
}

boost::statechart::result sanguis::server::running_state::operator()(const net::id_type id,const messages::client_info&m) 
{
	sge::clog << SGE_TEXT("server: received client info from ") << id << SGE_TEXT("\n");
	create_game(id,m);
	return discard_event();
}

boost::statechart::result sanguis::server::running_state::operator()(const net::id_type id,const messages::disconnect&) 
{
	if (player_->id() != id)
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
