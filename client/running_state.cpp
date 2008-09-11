#include "running_state.hpp"
#include "intermediate_state.hpp"
#include "next_id.hpp"
#include "../client_entity_type.hpp"
#include "../dispatch_type.hpp"
#include "../client_messages/add.hpp"
#include "../messages/assign_id.hpp"
#include "../messages/disconnect.hpp"
#include "../messages/give_weapon.hpp"
#include "../messages/move.hpp"
#include "../messages/pause.hpp"
#include "../messages/remove.hpp"
#include "../messages/unpause.hpp"
#include "../draw/coord_transform.hpp"
#include <boost/mpl/vector.hpp>
#include <boost/bind.hpp>

namespace
{

sanguis::entity_id const
	cursor_id(sanguis::client::next_id()),
	background_id(sanguis::client::next_id()),
	healthbar_id(sanguis::client::next_id());

}

sanguis::client::running_state::running_state(
	my_context ctx)
:
	my_base(ctx), 
	drawer(
		context<machine>().renderer(),
		context<machine>().font()),
	logic_(
		boost::bind(&running_state::send_message, this, _1),
		context<machine>().renderer()),
	input(
		boost::bind(&logic::handle_player_action, &logic_, _1)),
	input_connection(
		context<machine>().con_wrapper().register_callback(
			boost::bind(&input_handler::input_callback, &input, _1)))
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

	// update: cursor pos (TODO: this should be done in a better way)
	drawer.process_message(
		messages::move(
			cursor_id,
			screen_to_virtual(
				context<machine>().renderer()->screen_size(),
				logic_.cursor_pos())));

	drawer.draw(t.delta());
	
	return discard_event();
}

boost::statechart::result
sanguis::client::running_state::react(
	message_event const &m)
{
	return dispatch_type<
		boost::mpl::vector<
			messages::assign_id,
			messages::disconnect,
			messages::give_weapon,
			messages::move,
			messages::pause,
			messages::remove,
			messages::unpause
		>,
		boost::statechart::result>(
		*this,
		*m.message,
		boost::bind(&running_state::handle_default_msg, this, _1));
}

boost::statechart::result
sanguis::client::running_state::operator()(
	messages::assign_id const &m)
{
	logic_.player_id(
		m.player_id());
	return discard_event();
}

boost::statechart::result
sanguis::client::running_state::operator()(
	messages::disconnect const &)
{
	return transit<intermediate_state>();
}

boost::statechart::result
sanguis::client::running_state::operator()(
	messages::give_weapon const &m)
{
	logic_.give_weapon(
			m);
	return discard_event();
}

boost::statechart::result
sanguis::client::running_state::operator()(
	messages::move const &m)
{
	logic_.move(
		m);
	drawer.process_message(
		m);
	return discard_event();
}

boost::statechart::result
sanguis::client::running_state::operator()(
	messages::pause const &)
{
	logic_.pause(true);
	drawer.pause(true);
	return discard_event();
}

boost::statechart::result
sanguis::client::running_state::operator()(
	messages::remove const &m)
{
	logic_.remove(
		m.id());
	drawer.process_message(
		m);
	// TODO: check the logic if we died
	return discard_event();
}

boost::statechart::result
sanguis::client::running_state::operator()(
	messages::unpause const &)
{
	logic_.pause(false);
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
	context<machine>().send(
		m);
}
