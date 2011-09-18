#include <sanguis/client/control/actions/cursor.hpp>

sanguis::client::control::actions::cursor::cursor(
	control::cursor_position const &_position
)
:
	position_(_position)
{
}

sanguis::client::control::cursor_position const
sanguis::client::control::actions::cursor::position() const
{
	return position_;
}
