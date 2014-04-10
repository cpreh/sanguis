#include <sanguis/client/control/key_scale.hpp>
#include <sanguis/client/control/actions/scale.hpp>
#include <sanguis/client/control/actions/scale_type.hpp>


sanguis::client::control::actions::scale::scale(
	sanguis::client::control::actions::scale_type const _type,
	sanguis::client::control::key_scale const _scale
)
:
	type_(
		_type
	),
	scale_(
		_scale
	)
{
}

sanguis::client::control::actions::scale_type
sanguis::client::control::actions::scale::type() const
{
	return type_;
}

sanguis::client::control::key_scale
sanguis::client::control::actions::scale::get() const
{
	return scale_;
}
