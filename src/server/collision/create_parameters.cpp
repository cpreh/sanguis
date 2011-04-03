#include "create_parameters.hpp"
#include <fcppt/math/vector/basic_impl.hpp>

sanguis::server::collision::create_parameters::create_parameters(
	sge::projectile::world &_world,
	server::center const &_center,
	collision::global_groups const &_global_groups
)
:
	world_(_world),
	center_(_center),
	global_groups_(_global_groups)
{
}

sge::projectile::world &
sanguis::server::collision::create_parameters::world() const
{
	return world_;
}

sanguis::server::center const
sanguis::server::collision::create_parameters::center() const
{
	return center_;
}

sanguis::server::collision::global_groups const &
sanguis::server::collision::create_parameters::global_groups() const
{
	return global_groups_;
}
