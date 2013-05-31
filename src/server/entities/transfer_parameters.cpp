#include <sanguis/server/angle.hpp>
#include <sanguis/server/center.hpp>
#include <sanguis/server/collision/global_groups_fwd.hpp>
#include <sanguis/server/entities/transfer_parameters.hpp>
#include <sge/projectile/world_fwd.hpp>
#include <sge/projectile/body/object_fwd.hpp>


sanguis::server::entities::transfer_parameters::transfer_parameters(
	sge::projectile::world &_world,
	sge::projectile::body::object const *const _static_body,
	sanguis::server::center const &_center,
	sanguis::server::collision::global_groups const &_global_groups,
	sanguis::server::angle const _angle
)
:
	world_(
		_world
	),
	static_body_(
		_static_body
	),
	center_(
		_center
	),
	global_groups_(
		_global_groups
	),
	angle_(
		_angle
	)
{
}

sge::projectile::world &
sanguis::server::entities::transfer_parameters::world() const
{
	return world_;
}

sge::projectile::body::object const *
sanguis::server::entities::transfer_parameters::static_body() const
{
	return static_body_;
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
