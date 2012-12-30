#include <sanguis/client/control/actions/nullary.hpp>
#include <sanguis/client/control/actions/nullary_type.hpp>


sanguis::client::control::actions::nullary::nullary(
	sanguis::client::control::actions::nullary_type const _type
)
:
	type_(
		_type
	)
{
}

sanguis::client::control::actions::nullary_type
sanguis::client::control::actions::nullary::type() const
{
	return type_;
}
