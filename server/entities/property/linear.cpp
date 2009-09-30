#ifndef SANGUIS_SERVER_ENTITIES_PROPERTY_LINEAR_IMPL_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_PROPERTY_LINEAR_IMPL_HPP_INCLUDED

#include "linear.hpp"

sanguis::server::entities::property::linear::linear()
:
	value_(
		1
	)
{}

void
sanguis::server::entities::property::linear::add(
	value_type const add_
)
{
	value_ += add_;
}

void
sanguis::server::entities::property::linear::remove(
	value_type const sub_
)
{
	value_ -= sub_;
}

sanguis::server::entities::property::linear::value_type
sanguis::server::entities::property::linear::value() const
{
	return value_;
}

#endif
