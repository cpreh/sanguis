#include "player_action.hpp"

sanguis::client::control::player_action::player_action(
	action_type::type const type_,
	key_scale const scale_
)
:
	type_(type_),
	scale_(scale_)
{}

sanguis::client::control::action_type::type
sanguis::client::control::player_action::type() const
{
	return type_;
}

sanguis::client::control::key_scale
sanguis::client::control::player_action::scale() const
{
	return scale_;
}
