#include "player_action.hpp"

sanguis::client::player_action::player_action(
	const action_type type_,
	const key_scale scale_)
: type_(type_),
  scale_(scale_)
{}

sanguis::client::player_action::action_type
sanguis::client::player_action::type() const
{
	return type_;
}

sanguis::client::key_scale
sanguis::client::player_action::scale() const
{
	return scale_;
}
