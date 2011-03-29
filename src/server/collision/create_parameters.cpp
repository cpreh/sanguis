#include "create_parameters.hpp"
#include <fcppt/math/vector/basic_impl.hpp>

sanguis::server::collision::create_parameters::create_parameters(
	server::pos const &_center,
	server::pos const &_speed
)
:
	center_(_center),
	speed_(_speed)
{
}

sanguis::server::pos const
sanguis::server::collision::create_parameters::center() const
{
	return center_;
}

sanguis::server::pos const
sanguis::server::collision::create_parameters::speed() const
{
	return speed_;
}
