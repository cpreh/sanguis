#include <sanguis/client/control/optional_cursor_position.hpp>
#include <sanguis/client/control/actions/cursor.hpp>


sanguis::client::control::actions::cursor::cursor(
	sanguis::client::control::optional_cursor_position const _position
)
:
	position_(
		_position
	)
{
}

sanguis::client::control::optional_cursor_position
sanguis::client::control::actions::cursor::position() const
{
	return
		position_;
}
