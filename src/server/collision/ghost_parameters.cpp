#include "ghost_parameters.hpp"

sanguis::server::collision::ghost_parameters::ghost_parameters(
	sge::projectile::world &_world,
	collision::group_vector const &_groups,
	collision::global_groups const &_global_groups
)
:
	world_(_world),
	groups_(_groups),
	global_groups_(_global_groups)
{
}

sge::projectile::world &
sanguis::server::collision::ghost_parameters::world() const
{
	return world_;
}

sanguis::server::collision::group_vector const &
sanguis::server::collision::ghost_parameters::groups() const
{
	return groups_;
}

sanguis::server::collision::global_groups const &
sanguis::server::collision::ghost_parameters::global_groups() const
{
	return global_groups_;
}
