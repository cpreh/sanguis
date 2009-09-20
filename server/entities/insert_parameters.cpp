#include "insert_parameters.hpp"
#include <sge/math/vector/basic_impl.hpp>

sanguis::server::entities::insert_parameters::insert_parameters(
	pos_type const &center_,
	space_unit const angle_and_direction_
)
:
	center_(center_),
	angle_(angle_and_direction_),
	direction_(angle_and_direction_)
{}

sanguis::server::entities::insert_parameters::insert_parameters(
	pos_type const &center_,
	space_unit const angle_,
	space_unit const direction_
)
:
	center_(center_),
	angle_(angle_),
	direction_(direction_)
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

sanguis::server::space_unit
sanguis::server::entities::insert_parameters::direction() const
{
	return direction_;
}
