#include "player_action.hpp"

sanguis::client::control::player_action::player_action(
	action_type::type const _type,
	key_scale const _scale
)
:
	type_(_type),
	scale_(_scale)
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
