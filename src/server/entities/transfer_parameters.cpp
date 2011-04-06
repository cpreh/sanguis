#include "transfer_parameters.hpp"

sanguis::server::entities::transfer_parameters::transfer_parameters(
	sge::projectile::world &_world,
	server::center const &_center,
	collision::global_groups const &_global_groups,
	server::angle const _angle
)
:
	world_(_world),
	center_(_center),
	global_groups_(_global_groups),
	angle_(_angle)
{
}

sge::projectile::world &
sanguis::server::entities::transfer_parameters::world() const
{
	return world_;
}

sanguis::server::center const
sanguis::server::entities::transfer_parameters::center() const
{
	return center_;
}

sanguis::server::collision::global_groups const &
sanguis::server::entities::transfer_parameters::global_groups() const
{
	return global_groups_;
}

sanguis::server::angle const
sanguis::server::entities::transfer_parameters::angle() const
{
	return angle_;
}
