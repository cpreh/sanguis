#include "insert_parameters.hpp"
#include <fcppt/math/vector/basic_impl.hpp>

sanguis::server::entities::insert_parameters::insert_parameters(
	server::center const &_center,
	server::angle const _angle
)
:
	center_(_center),
	angle_(_angle)
{
}

sanguis::server::center const &
sanguis::server::entities::insert_parameters::center() const
{
	return center_;
}

sanguis::server::angle const
sanguis::server::entities::insert_parameters::angle() const
{
	return angle_;
}
