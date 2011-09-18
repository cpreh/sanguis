#include <sanguis/client/control/actions/nullary.hpp>

sanguis::client::control::actions::nullary::nullary(
	actions::nullary_type::type const _type
)
:
	type_(_type)
{
}

sanguis::client::control::actions::nullary_type::type
sanguis::client::control::actions::nullary::type() const
{
	return type_;
}
