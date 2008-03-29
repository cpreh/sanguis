#include "running_state.hpp"
#include "player_action.hpp"
#include "intermediate_state.hpp"
#include "client_id.hpp"
#include "../dispatch_type.hpp"
#include "../truncation_check_cast.hpp"
#include "../truncation_check_structure_cast.hpp"
#include "../messages/add.hpp"
#include "../messages/disconnect.hpp"
#include "../messages/game_state.hpp"
#include "../messages/move.hpp"
#include "../messages/player_direction_event.hpp"
#include "../messages/player_rotation_event.hpp"
#include "../messages/player_start_shooting.hpp"
#include "../messages/player_stop_shooting.hpp"
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
#include <typeinfo>
#include <cmath>

namespace
{

const sanguis::entity_id cursor_id(sanguis::client::next_client_id());

}

sanguis::client::running_state::running_state(my_context ctx)
: my_base(ctx), 
  drawer(context<machine>().sys.renderer),
  input(boost::bind(&running_state::handle_player_action, this, _1)),
  input_connection(
	context<machine>().con_wrapper.register_callback(
		boost::bind(&input_handler::input_callback, &input, _1))),
  direction(0, 0),
  cursor_pos(0, 0)
{
	sge::clog << SGE_TEXT("client: entering running state\n");
	drawer.process_message(
		messages::add(
			::cursor_id,
			entity_type::cursor,
			truncation_check_structure_cast<messages::vector2>(cursor_pos),
			static_cast<messages::space_unit>(0),
			messages::vector2(static_cast<messages::space_unit>(0),static_cast<messages::space_unit>(0))));
}

boost::statechart::result sanguis::client::running_state::react(const tick_event&t)
{
	sge::window::dispatch();
	machine &m = context<machine>();
	m.sys.input_system->dispatch();
	
	// show text in the screen center (hopefully)
	m.font.draw_text(SGE_TEXT("running"),
		sge::font_pos(0,0),sge::font_dim(
			m.sys.renderer->screen_width(),
			m.sys.renderer->screen_height()),
		sge::font_align_h::center,sge::font_align_v::center);

	drawer.draw(t.data);
	
	return discard_event();
}

boost::statechart::result sanguis::client::running_state::react(const message_event &m)
{
	return dispatch_type<
		boost::mpl::vector<
			messages::disconnect,
			messages::game_state
		>,
		boost::statechart::result>(
		*this,
		*m.message,
		boost::bind(&running_state::handle_default_msg, this, _1));
}

boost::statechart::result
sanguis::client::running_state::operator()(
	const messages::disconnect&)
{
	sge::clog << SGE_TEXT("client: disconnected\n");
	return transit<intermediate_state>();
}

boost::statechart::result
sanguis::client::running_state::operator()(
	const messages::game_state&)
{
	sge::clog << SGE_TEXT("client: running: received game state\n");
	return discard_event();
}

boost::statechart::result
sanguis::client::running_state::handle_default_msg(const messages::base& m)
{
	drawer.process_message(m);
	return discard_event();
}

void sanguis::client::running_state::handle_player_action(const player_action& m)
{
	// TODO: accumulate events!
	try
	{
		// TODO: install handler logic for this
		const draw::player& player(drawer.get_player());
		handle_direction(player, m);
		handle_rotation(player, m);
		handle_shooting(player, m);
	}
	catch(const sge::exception& e)
	{
		sge::clog << e.what() << SGE_TEXT('\n');
	}
}

void sanguis::client::running_state::handle_direction(
	const draw::player& player,
	const player_action& m)
{
	const sge::math::vector2 last_direction(direction);
	
	switch(m.type()) {
	case player_action::horizontal_move:
		direction.x() += m.scale();
		break;
	case player_action::vertical_move:
		direction.y() += m.scale();
		break;
	default:
		return;
	}

	if(last_direction != direction)
		context<machine>().send(
			new messages::player_direction_event(
				player.id(),
				sge::math::structure_cast<messages::space_unit>(direction)));
}

void sanguis::client::running_state::handle_rotation(
	const draw::player& player,
	const player_action& m)
{
	const sge::sprite::point last_cursor_pos(cursor_pos);

	switch(m.type()) {
	case player_action::horizontal_look:
		cursor_pos.x() += static_cast<sge::sprite_unit>(m.scale());
		break;
	case player_action::vertical_look:
		cursor_pos.y() += static_cast<sge::sprite_unit>(m.scale());
		break;
	default:
		return;
	}

	const sge::renderer_ptr rend = context<machine>().sys.renderer;
	cursor_pos.x() = sge::math::clamp(cursor_pos.x(), 0, static_cast<sge::sprite_unit>(rend->screen_width()));
	cursor_pos.y() = sge::math::clamp(cursor_pos.y(), 0, static_cast<sge::sprite_unit>(rend->screen_height()));
	
	if(last_cursor_pos == cursor_pos)
		return;
		
	const boost::optional<sge::space_unit> rotation(sge::math::angle_to<sge::space_unit>(player.center(), cursor_pos));
	if(!rotation)
		return;

	context<machine>().send(
		new messages::player_rotation_event(
			player.id(),
			static_cast<messages::space_unit>(
				*rotation)));

	drawer.process_message(
		messages::move(
			cursor_id,
			screen_to_virtual(rend->screen_size(),
			cursor_pos)));

}

void sanguis::client::running_state::handle_shooting(
	const draw::player& p,
	const player_action& m)
{
	if(m.type() != player_action::shoot)
		return;
	
	context<machine>().send(
		sge::math::compare(static_cast<key_scale>(0), m.scale())
		? static_cast<messages::base*>(
			new messages::player_stop_shooting(
				p.id()))
		: static_cast<messages::base*>(
			new messages::player_start_shooting(
				p.id())));
}
