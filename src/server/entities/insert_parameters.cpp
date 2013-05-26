#include <sanguis/server/angle.hpp>
#include <sanguis/server/center.hpp>
#include <sanguis/server/entities/insert_parameters.hpp>


sanguis::server::entities::insert_parameters::insert_parameters(
	sanguis::server::center const &_center,
	sanguis::server::angle const _angle
)
:
	center_(
		_center
	),
	angle_(
		_angle
	)
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
