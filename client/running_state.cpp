#include "running_state.hpp"
#include "player_action.hpp"
#include "intermediate_state.hpp"
#include "next_id.hpp"
#include "../client_entity_type.hpp"
#include "../cyclic_iterator_impl.hpp"
#include "../dispatch_type.hpp"
#include "../truncation_check_cast.hpp"
#include "../truncation_check_structure_cast.hpp"
#include "../client_messages/add.hpp"
#include "../messages/disconnect.hpp"
#include "../messages/game_state.hpp"
#include "../messages/give_weapon.hpp"
#include "../messages/move.hpp"
#include "../messages/pause.hpp"
#include "../messages/player_change_weapon.hpp"
#include "../messages/player_direction.hpp"
#include "../messages/player_pause.hpp"
#include "../messages/player_rotation.hpp"
#include "../messages/player_start_shooting.hpp"
#include "../messages/player_stop_shooting.hpp"
#include "../messages/player_unpause.hpp"
#include "../messages/unpause.hpp"
#include "../draw/player.hpp"
#include "../draw/coord_transform.hpp"
#include <sge/iostream.hpp>
#include <sge/string.hpp>
#include <sge/exception.hpp>
#include <sge/math/clamp.hpp>
#include <sge/math/vector.hpp>
#include <sge/math/angle.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/bind.hpp>
#include <algorithm>
#include <cmath>

namespace
{

const sanguis::entity_id cursor_id(sanguis::client::next_id()),
                         background_id(sanguis::client::next_id()),
                         healthbar_id(sanguis::client::next_id());

}

sanguis::client::running_state::running_state(my_context ctx)
: my_base(ctx), 
  drawer(
	context<machine>().renderer(),
	context<machine>().font()),
  logic_(boost::bind(&running_state::send_message, this, _1)),
  input(boost::bind(&running_state::handle_player_action, this, _1)),
  input_connection(
	context<machine>().con_wrapper().register_callback(
		boost::bind(&input_handler::input_callback, &input, _1))),
  current_weapon(weapon_type::size)
{
	drawer.process_message(
		client_messages::add(
			::cursor_id,
			client_entity_type::cursor));

	drawer.process_message(
		client_messages::add(
			::background_id,
			client_entity_type::background));
}

boost::statechart::result
sanguis::client::running_state::react(
	tick_event const &t)
{
	context<machine>().dispatch();

	drawer.draw(t.delta());
	
	return discard_event();
}

boost::statechart::result
sanguis::client::running_state::react(
	message_event const &m)
{
	return dispatch_type<
		boost::mpl::vector<
			messages::disconnect,
			messages::game_state,
			messages::give_weapon,
			messages::pause,
			messages::unpause
		>,
		boost::statechart::result>(
		*this,
		*m.message,
		boost::bind(&running_state::handle_default_msg, this, _1));
}

boost::statechart::result
sanguis::client::running_state::operator()(
	messages::disconnect const &)
{
	sge::clog << SGE_TEXT("client: disconnected\n");
	return transit<intermediate_state>();
}

boost::statechart::result
sanguis::client::running_state::operator()(
	messages::game_state const &)
{
	sge::clog << SGE_TEXT("client: running: received game state\n");
	return discard_event();
}

boost::statechart::result
sanguis::client::running_state::operator()(
	messages::give_weapon const &m)
{
	logic.give_weapon(
		m);
	return discard_event();
}

boost::statechart::result
sanguis::client::running_state::operator()(
	messages::pause const &)
{
	logic.pause(true);
	drawer.pause(true);
	return discard_event();
}

boost::statechart::result
sanguis::client::running_state::operator()(
	messages::unpause const &)
{
	logic.pause(false);
	drawer.pause(false);
	return discard_event();
}

boost::statechart::result
sanguis::client::running_state::handle_default_msg(
	messages::base const &m)
{
	drawer.process_message(m);
	return discard_event();
}

void sanguis::client::running_state::send_message(
	messages::auto_ptr m)
{
	
}
