#ifndef SANGUIS_SERVER_ENTITIES_PROPERTY_LINEAR_IMPL_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_PROPERTY_LINEAR_IMPL_HPP_INCLUDED

#include <sanguis/server/entities/property/linear.hpp>

sanguis::server::entities::property::linear::linear()
:
	value_(
		1
	)
{}

void
sanguis::server::entities::property::linear::change(
	value_type const _add
)
{
	value_ += _add;
}

sanguis::server::entities::property::linear::value_type
sanguis::server::entities::property::linear::value() const
{
	return value_;
}

#endif
