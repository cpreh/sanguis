#include <sanguis/client/control/actions/any.hpp>
#include <sanguis/client/events/action.hpp>


sanguis::client::events::action::action(
	sanguis::client::control::actions::any const _value
)
:
	value_(
		_value
	)
{
}

sanguis::client::events::action::action(
	action &&
)
noexcept
= default;

sanguis::client::events::action::action(
	action const &
)
= default;

sanguis::client::events::action &
sanguis::client::events::action::operator=(
	action &&
)
noexcept
= default;

sanguis::client::events::action &
sanguis::client::events::action::operator=(
	action const &
)
= default;

sanguis::client::events::action::~action()
= default;

sanguis::client::control::actions::any const &
sanguis::client::events::action::value() const
{
	return
		value_;
}
