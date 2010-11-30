#include "insert_parameters.hpp"
#include <fcppt/math/vector/basic_impl.hpp>

sanguis::server::entities::insert_parameters::insert_parameters(
	pos_type const &_center,
	space_unit const _angle
)
:
	center_(_center),
	angle_(_angle)
{}

sanguis::server::pos_type const &
sanguis::server::entities::insert_parameters::center() const
{
	return center_;
}

sanguis::server::space_unit
sanguis::server::entities::insert_parameters::angle() const
{
	return angle_;
}
