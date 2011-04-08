#ifndef SANGUIS_CLIENT_CONTROL_INPUT_TRANSLATOR_HPP_INCLUDED
#define SANGUIS_CLIENT_CONTROL_INPUT_TRANSLATOR_HPP_INCLUDED

#include "input_translator_fwd.hpp"
#include "actions/binary_callback.hpp"
#include "actions/cursor_callback.hpp"
#include "actions/nullary_callback.hpp"
#include "actions/nullary_type.hpp"
#include "actions/scale_callback.hpp"
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
	input_translator(
		sge::input::keyboard::device_ptr,
		client::cursor::object &,
		actions::binary_callback const &,
		actions::cursor_callback const &,
		actions::nullary_callback const &,
		actions::scale_callback const &
	);

	~input_translator();
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
	nullary_event(
		bool pressed,
		actions::nullary_type::type
	);

	actions::binary_callback const binary_callback_;

	actions::cursor_callback const cursor_callback_;

	actions::nullary_callback const nullary_callback_;

	actions::scale_callback const scale_callback_;

	fcppt::signal::scoped_connection const
		key_connection_,
		axis_connection_,
		button_connection_;
};

}
}
}

#endif
