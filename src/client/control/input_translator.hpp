#ifndef SANGUIS_CLIENT_CONTROL_INPUT_TRANSLATOR_HPP_INCLUDED
#define SANGUIS_CLIENT_CONTROL_INPUT_TRANSLATOR_HPP_INCLUDED

#include "action_type.hpp"
#include "input_translator_fwd.hpp"
#include "player_action_fwd.hpp"
#include "../cursor/object_fwd.hpp"
#include <sge/input/keyboard/device_ptr.hpp>
#include <sge/input/keyboard/key_event_fwd.hpp>
#include <sge/input/cursor/move_event_fwd.hpp>
#include <sge/input/cursor/button_event_fwd.hpp>
#include <sge/input/cursor/position_unit.hpp>
#include <fcppt/function/object.hpp>
#include <fcppt/signal/scoped_connection.hpp>
#include <fcppt/noncopyable.hpp>

namespace sanguis
{
namespace client
{
namespace control
{

class input_translator
{
	FCPPT_NONCOPYABLE(
		input_translator
	);
public:
	typedef fcppt::function::object<
		void (player_action const &)
	> post_fun;

	explicit input_translator(
		sge::input::keyboard::device_ptr,
		client::cursor::object &,
		post_fun const &
	);
private:
	void
	key_callback(
		sge::input::keyboard::key_event const &
	);

	void
	move_callback(
		sge::input::cursor::move_event const &
	);

	void
	button_callback(
		sge::input::cursor::button_event const &
	);

	void
	direction_event(
		sge::input::keyboard::key_event const &
	);

	void
	rotation_event(
		sge::input::cursor::position_unit,
		action_type::type
	);

	void
	weapon_switch_event(
		bool pressed,
		action_type::type
	);

	void
	perk_event(
		bool pressed
	);

	void
	escape_event(
		bool pressed
	);

	post_fun const post_message_;

	fcppt::signal::scoped_connection const
		key_connection_,
		axis_connection_,
		button_connection_;
};

}
}
}

#endif
