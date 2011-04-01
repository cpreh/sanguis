#include "create_parameters.hpp"
#include <fcppt/math/vector/basic_impl.hpp>

sanguis::server::collision::create_parameters::create_parameters(
	server::center const &_center,
	server::speed const &_speed,
	collision::user_data const &_user_data,
	collision::global_groups const &_global_groups
)
:
	center_(_center),
	speed_(_speed),
	user_data_(_user_data),
	global_groups_(_global_groups)
{
}

sanguis::server::center const
sanguis::server::collision::create_parameters::center() const
{
	return center_;
}

sanguis::server::speed const
sanguis::server::collision::create_parameters::speed() const
{
	return speed_;
}

sanguis::server::collision::user_data const &
sanguis::server::collision::create_parameters::user_data() const
{
	return user_data_;
}

sanguis::server::collision::global_groups const &
sanguis::server::collision::create_parameters::global_groups() const
{
	return global_groups_;
}
