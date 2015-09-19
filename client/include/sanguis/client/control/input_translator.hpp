#ifndef SANGUIS_CLIENT_CONTROL_INPUT_TRANSLATOR_HPP_INCLUDED
#define SANGUIS_CLIENT_CONTROL_INPUT_TRANSLATOR_HPP_INCLUDED

#include <sanguis/client/control/input_translator_fwd.hpp>
#include <sanguis/client/control/actions/binary_type_fwd.hpp>
#include <sanguis/client/control/actions/callback.hpp>
#include <sanguis/client/control/actions/nullary_type_fwd.hpp>
#include <sge/input/cursor/activatable.hpp>
#include <sge/input/cursor/button_event_fwd.hpp>
#include <sge/input/cursor/move_event_fwd.hpp>
#include <sge/input/cursor/object_fwd.hpp>
#include <sge/input/cursor/position_unit.hpp>
#include <sge/input/focus/key_event_fwd.hpp>
#include <sge/input/focus/object_fwd.hpp>
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
		sge::input::focus::object &,
		sge::input::cursor::object &,
		sanguis::client::control::actions::callback const &
	);

	~input_translator();

	sge::input::cursor::activatable &
	cursor();
private:
	void
	key_callback(
		sge::input::focus::key_event const &
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
		sge::input::focus::key_event const &
	);

	void
	nullary_event(
		bool pressed,
		sanguis::client::control::actions::nullary_type
	);

	void
	binary_event(
		bool pressed,
		sanguis::client::control::actions::binary_type
	);

	sge::input::cursor::activatable cursor_;

	sanguis::client::control::actions::callback const callback_;

	fcppt::signal::scoped_connection const
		key_connection_,
		axis_connection_,
		button_connection_;
};

}
}
}

#endif
