#include "create_parameters.hpp"
#include <sge/math/vector/basic_impl.hpp>

sanguis::server::collision::create_parameters::create_parameters(
	pos_type const &center_,
	pos_type const &speed_
)
:
	center_(center_),
	speed_(speed_)
{}

sanguis::server::pos_type const
sanguis::server::collision::create_parameters::center() const
{
	return center_;
}

sanguis::server::pos_type const
sanguis::server::collision::create_parameters::speed() const
{
	return speed_;
}
