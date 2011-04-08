#include "binary.hpp"

sanguis::client::control::actions::binary::binary(
	actions::binary_type::type const _type,
	bool const _value
)
:
	type_(_type),
	value_(_value)
{
}

sanguis::client::control::actions::binary_type::type
sanguis::client::control::actions::binary::type() const
{
	return type_;
}

bool
sanguis::client::control::actions::binary::value() const
{
	return value_;
}
