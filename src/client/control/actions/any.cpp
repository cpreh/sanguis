#include "any.hpp"

sanguis::client::control::actions::any::any(
	actions::variant const &_variant
)
:
	variant_(_variant)
{
}

sanguis::client::control::actions::variant const &
sanguis::client::control::actions::any::get() const
{
	return variant_;
}
