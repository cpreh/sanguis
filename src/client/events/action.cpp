#include <sanguis/client/events/action.hpp>

sanguis::client::events::action::action(
	client::control::actions::any const &_value
)
:
	value_(_value)
{
}

sanguis::client::control::actions::any const
sanguis::client::events::action::value() const
{
	return value_;
}
