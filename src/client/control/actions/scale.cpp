#include <sanguis/client/control/actions/scale.hpp>

sanguis::client::control::actions::scale::scale(
	scale_type::type const _type,
	key_scale const _scale
)
:
	type_(_type),
	scale_(_scale)
{
}

sanguis::client::control::actions::scale_type::type
sanguis::client::control::actions::scale::type() const
{
	return type_;
}

sanguis::client::control::key_scale
sanguis::client::control::actions::scale::get() const
{
	return scale_;
}
