#include "running_state.hpp"
#include "player_action.hpp"
#include "intermediate_state.hpp"
#include "../dispatch_type.hpp"
#include "../messages/add.hpp"
#include "../messages/disconnect.hpp"
#include "../messages/game_state.hpp"
#include "../messages/move.hpp"
#include "../messages/player_direction_event.hpp"
#include "../messages/player_rotation_event.hpp"
#include "../draw/player.hpp"
#include <sge/iostream.hpp>
#include <sge/string.hpp>
#include <sge/exception.hpp>
#include <sge/renderer/scoped_renderblock.hpp>
#include <sge/math/clamp.hpp>
#include <sge/math/constants.hpp>
#include <sge/math/vector.hpp>
#include <sge/math/compare.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/bind.hpp>
#include <typeinfo>
#include <cmath>

sanguis::client::running_state::running_state(my_context ctx)
: my_base(ctx), 
  drawer(context<machine>().sys.renderer),
  input(boost::bind(&running_state::handle_player_action, this, _1)),
  input_connection(
  	context<machine>().sys.input_system->register_callback(
		boost::bind(&input_handler::input_callback, &input, _1))),
  cursor_id(1337)
{
	sge::clog << SGE_TEXT("client: entering running state\n"); 

	drawer.process_message(
		messages::add(
			cursor_id,
			entity_type::cursor,
			// FIXME: truncation_structure_cast (twice)
			cursor_pos,
			sge::sprite_texture_dim,
			static_cast<messages::space_unit>(0),
			messages::vector2(static_cast<messages::space_unit>(0),static_cast<messages::space_unit>(0))));
}

boost::statechart::result sanguis::client::running_state::react(const tick_event&t)
{
	sge::window::dispatch();
	machine &m = context<machine>();
	m.sys.input_system->dispatch();
	const sge::scoped_renderblock block_(m.sys.renderer);
	
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
	const sge::sprite::point last_cursor_pos(cursor_pos);
	const sge::math::vector2 last_direction(direction);
	// TODO: accumulate events!
	switch(m.type()) {
	case player_action::horizontal_move:
		direction.x() += m.scale();
		break;
	case player_action::vertical_move:
		direction.y() += m.scale();
		break;
	case player_action::horizontal_look:
		cursor_pos.x() += static_cast<sge::sprite_unit>(m.scale());
		break;
	case player_action::vertical_look:
		cursor_pos.y() += static_cast<sge::sprite_unit>(m.scale());
		break;
	default:
		break;
	}

	const sge::renderer_ptr rend = context<machine>().sys.renderer;
	cursor_pos.x() = sge::math::clamp(cursor_pos.x(), 0, static_cast<sge::sprite_unit>(rend->screen_width()));
	cursor_pos.y() = sge::math::clamp(cursor_pos.y(), 0, static_cast<sge::sprite_unit>(rend->screen_height()));
	
	try
	{
		const draw::player& player(drawer.get_player());
		if(last_direction != direction)
		{
	//		sge::clog << SGE_TEXT("client: sending direction ") << direction << SGE_TEXT('\n');
			context<machine>().push_back(new messages::player_direction_event(player.id(),sge::math::structure_cast<messages::space_unit>(direction)));
		}

		if(last_cursor_pos == cursor_pos)
			return;
	
		const sge::sprite_point d = player.center() - cursor_pos;
		const sge::space_unit len = sge::math::structure_cast<sge::space_unit>(d).length();
		if(sge::math::almost_zero(len))
			return;
		const sge::space_unit rad = std::asin(static_cast<sge::space_unit>(d.x()) / len);
		const sge::space_unit rotation(d.y() >= 0 ? rad : -rad + sge::math::pi<sge::space_unit>());

	//	sge::clog << SGE_TEXT("client: sending rotation ") << rotation << SGE_TEXT('\n');
		context<machine>().push_back(new messages::player_rotation_event(player.id(), static_cast<messages::space_unit>(rotation)));

		drawer.process_message(
			messages::move(
				cursor_id,
				// FIXME: structure_truncation_cast
				cursor_pos));
	}
	catch(const sge::exception& e)
	{
		sge::clog << SGE_TEXT("player not found in scene_drawer: \"")
		          << e.what()
			  << SGE_TEXT("\"!\n");
	}
}
