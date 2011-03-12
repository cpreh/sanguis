#include "action.hpp"

sanguis::client::events::action::action(
	control::player_action const &_value
)
:
	value_(_value)
{}

sanguis::client::control::player_action
sanguis::client::events::action::value() const
{
	return value_;
}
