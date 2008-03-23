#include "running_state.hpp"
#include "waiting_state.hpp"
#include "get_unique_id.hpp"
#include "../messages/player_rotation_event.hpp"
#include "../messages/player_direction_event.hpp"
#include "../messages/add.hpp"
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
#include "message_functor.hpp"

#include <sge/iostream.hpp>
#include <sge/su.hpp>
#include <sge/string.hpp>
#include <sge/math/vector.hpp>
#include <sge/math/atan2.hpp>

#include <boost/bind.hpp>
#include <boost/mpl/vector.hpp>

#include <cmath>

sanguis::server::running_state::running_state()
	: send_timer(sge::second()/2),
	  player_speed(SGE_TEXT("player_speed"),sge::su(80))
{
	sge::clog << SGE_TEXT("server: entering running state\n");
}

boost::statechart::result sanguis::server::running_state::react(const tick_event&t) 
{
	const sge::timer::frames_type delta = t.data.diff_time;
	player.pos += player.speed * delta;
	//sge::cout << "server (" << delta << ": " << player.pos << "\n";

	if (send_timer.update_b())
	{
		context<machine>().push_back(
			new messages::move(player.id,sge::math::structure_cast<boost::int32_t>(player.pos)));
	}
	return discard_event();
}

void sanguis::server::running_state::create_game(const messages::client_info &m)
{
	player.id =     get_unique_id();
	player.name =   sge::string(m.name.begin(),m.name.end());
	player.pos =    sge::math::vector2(sge::su(0),sge::su(0));
	player.angle =  sge::su(0);
	player.dim =    sge::math::dim2(sge::su(128),sge::su(128));
	player.speed =  sge::math::vector2(sge::su(0),sge::su(0));

	// send player entity, game state and player state
	sge::clog << "server: sending game messages\n";
	context<machine>().push_back(new messages::game_state(game_state(truncation_check_cast<boost::uint32_t>(0))));
	context<machine>().push_back(
		new messages::add(player.id,entity_type::player,
		// FIXME: truncation_structure_cast
			sge::math::structure_cast<boost::int32_t>(player.pos),
//			sge::math::structure_cast<boost::int32_t>(player.dim),
			player.angle,messages::vector2()));
	context<machine>().push_back(new messages::player_state(player.id,player_state(weapon_type::pistol,truncation_check_cast<boost::uint32_t>(0))));
}

boost::statechart::result sanguis::server::running_state::operator()(const net::id_type,const messages::player_rotation_event &e)
{
	player.angle = e.angle();
	context<machine>().push_back(new messages::rotate(player.id,static_cast<messages::space_unit>(player.angle)));
	return discard_event();
}

boost::statechart::result sanguis::server::running_state::operator()(const net::id_type,const messages::player_direction_event &e)
{
	if (e.dir().is_null())
		player.speed = sge::math::vector2();
	else
		player.speed = sge::math::normalize(e.dir()) * player_speed.value();

	context<machine>().push_back(new messages::speed(player.id,sge::math::structure_cast<messages::space_unit>(player.speed)));
	return discard_event();
}

boost::statechart::result sanguis::server::running_state::operator()(const net::id_type,const messages::client_info&m) 
{
	create_game(m);
	return discard_event();
}

boost::statechart::result sanguis::server::running_state::operator()(const net::id_type,const messages::disconnect&) 
{
	sge::clog << SGE_TEXT("server: disconnected\n");
	return transit<waiting_state>();
}

boost::statechart::result sanguis::server::running_state::handle_default_msg(const net::id_type,const messages::base&m) 
{
	sge::clog << SGE_TEXT("server: received unexpected message ") << typeid(m).name() << SGE_TEXT("\n");
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
			messages::player_direction_event
		>,
		boost::statechart::result>(
		mf,
		*m.message,
		boost::bind(&running_state::handle_default_msg, this, m.id, _1));
}
