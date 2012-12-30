#ifndef SANGUIS_CLIENT_CONTROL_INPUT_TRANSLATOR_HPP_INCLUDED
#define SANGUIS_CLIENT_CONTROL_INPUT_TRANSLATOR_HPP_INCLUDED

#include <sanguis/client/control/input_translator_fwd.hpp>
#include <sanguis/client/control/actions/callback.hpp>
#include <sanguis/client/control/actions/nullary_type.hpp>
#include <sanguis/client/cursor/object_fwd.hpp>
#include <sge/input/keyboard/device_fwd.hpp>
#include <sge/input/keyboard/key_event_fwd.hpp>
#include <sge/input/cursor/move_event_fwd.hpp>
#include <sge/input/cursor/button_event_fwd.hpp>
#include <sge/input/cursor/position_unit.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/signal/scoped_connection.hpp>


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
		sge::input::keyboard::device &,
		client::cursor::object &,
		actions::callback const &
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

	actions::callback const callback_;

	fcppt::signal::scoped_connection const
		key_connection_,
		axis_connection_,
		button_connection_;
};

}
}
}

#endif
