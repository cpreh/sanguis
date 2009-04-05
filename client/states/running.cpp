#include "running.hpp"
#include "menu.hpp"
#include "../next_id.hpp"
#include "../../client_entity_type.hpp"
#include "../../client_messages/add.hpp"
#include "../../messages/unwrap.hpp"
#include "../../draw/coord_transform.hpp"
#include "../../draw/scene.hpp"
#include "../../load/context.hpp"
#include <sge/renderer/state/list.hpp>
#include <sge/renderer/device.hpp>
#include <sge/audio/player.hpp>
#include <sge/audio/pool.hpp>
#include <sge/renderer/state/var.hpp>
#include <sge/renderer/state/states.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/bind.hpp>

namespace
{

sanguis::entity_id const
	cursor_id(sanguis::client::next_id()),
	background_id(sanguis::client::next_id()),
	healthbar_id(sanguis::client::next_id());

}

sanguis::client::states::running::running(
	my_context ctx)
:
	my_base(ctx), 
	music_(
		context<machine>().console_wrapper().con,
		context<machine>().resources().resources()),
	drawer(
		new draw::scene(
			context<machine>().resources(),
			context<machine>().renderer(),
			context<machine>().font()
		)
	),
	logic_(
		boost::bind(
			&running::send_message,
			this,
			_1),
		context<machine>().renderer(),
		context<machine>().console_wrapper().con),
	input(
		boost::bind(
			&logic::handle_player_action,
			&logic_,
			_1)),
	input_connection(
		context<machine>().console_wrapper().register_callback(
			boost::bind(
				&input_handler::input_callback,
				&input,
				_1)))
{
	context<machine>().renderer()->state(
		sge::renderer::state::list
			(sge::renderer::state::bool_::clear_backbuffer = false)
			(sge::renderer::state::bool_::clear_zbuffer = false)
	);

	drawer->client_message(
		client_messages::add(
			::cursor_id,
			client_entity_type::cursor
		)
	);

	drawer->client_message(
		client_messages::add(
			::background_id,
			client_entity_type::background
		)
	);
}

sanguis::client::states::running::~running()
{}

void 
sanguis::client::states::running::draw(
	tick_event const &t)
{
	drawer->draw(t.delta());
}

void 
sanguis::client::states::running::process(
	tick_event const &)
{
	context<machine>().dispatch();
	context<machine>().sound_pool().update();
	music_.update();

	// update: cursor pos (TODO: this should be done in a better way)
	(*drawer)(
		messages::move(
			cursor_id,
			screen_to_virtual(
				context<machine>().renderer()->screen_size(),
				logic_.cursor_pos()
			)
		)
	);
}

void 
sanguis::client::states::running::pause(
	bool const b)
{
	logic_.pause(b);
	drawer->pause(b);
}

boost::statechart::result
sanguis::client::states::running::react(
	message_event const &m)
{
	return messages::unwrap<
		boost::mpl::vector<
			messages::assign_id,
			messages::disconnect,
			messages::give_weapon,
			messages::move,
			messages::remove
		>,
		boost::statechart::result
	>(
		*this,
		*m.message(),
		boost::bind(
			&running::handle_default_msg,
			this,
			_1
		)
	);
}

boost::statechart::result
sanguis::client::states::running::operator()(
	messages::assign_id const &m)
{
	logic_.player_id(
		m.get<messages::roles::entity_id>()
	);
	return discard_event();
}

boost::statechart::result
sanguis::client::states::running::operator()(
	messages::disconnect const &)
{
	return transit<menu>();
}

boost::statechart::result
sanguis::client::states::running::operator()(
	messages::give_weapon const &m)
{
	logic_.give_weapon(
			m);
	return discard_event();
}

boost::statechart::result
sanguis::client::states::running::operator()(
	messages::move const &m)
{
	logic_.move(m);
	(*drawer)(m);
	return discard_event();
}

boost::statechart::result
sanguis::client::states::running::operator()(
	messages::remove const &m)
{
	logic_.remove(
		m.get<messages::roles::entity_id>()
	);
	(*drawer)(m);
	// TODO: check the logic if we died
	return discard_event();
}

boost::statechart::result
sanguis::client::states::running::handle_default_msg(
	messages::base const &m)
{
	drawer->process_message(m);
	return discard_event();
}

void sanguis::client::states::running::send_message(
	messages::auto_ptr m)
{
	context<machine>().send(
		m);
}
