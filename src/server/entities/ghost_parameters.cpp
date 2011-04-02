#include "ghost_parameters.hpp"

sanguis::server::entities::ghost_parameters::ghost_parameters(
	sge::projectile::world &_world,
	collision::global_groups const &_global_groups,
	server::center const &_center
)
:
	world_(_world),
	global_groups_(_global_groups),
	center_(_center)
{
}

sge::projectile::world &
sanguis::server::entities::ghost_parameters::world() const
{
	return world_;
}

sanguis::server::collision::global_groups const &
sanguis::server::entities::ghost_parameters::global_groups() const
{
	return global_groups_;
}

sanguis::server::center const &
sanguis::server::entities::ghost_parameters::center() const
{
	return center_;
}
