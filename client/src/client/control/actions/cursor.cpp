#include <sanguis/client/control/optional_cursor_position.hpp>
#include <sanguis/client/control/actions/cursor.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


sanguis::client::control::actions::cursor::cursor(
	sanguis::client::control::optional_cursor_position _position
)
:
	position_(
		std::move(
			_position
		)
	)
{
}

sanguis::client::control::optional_cursor_position
sanguis::client::control::actions::cursor::position() const
{
	return
		position_;
}
