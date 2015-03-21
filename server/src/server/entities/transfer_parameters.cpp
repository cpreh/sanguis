#include <sanguis/collision/world/created.hpp>
#include <sanguis/collision/world/object_fwd.hpp>
#include <sanguis/creator/grid_fwd.hpp>
#include <sanguis/server/angle.hpp>
#include <sanguis/server/center.hpp>
#include <sanguis/server/entities/transfer_parameters.hpp>


sanguis::server::entities::transfer_parameters::transfer_parameters(
	sanguis::collision::world::object &_world,
	sanguis::collision::world::created const _created,
	sanguis::creator::grid const &_grid,
	sanguis::server::center const &_center,
	sanguis::server::angle const _angle
)
:
	world_(
		_world
	),
	created_{
		_created
	},
	grid_(
		_grid
	),
	center_(
		_center
	),
	angle_(
		_angle
	)
{
}

sanguis::collision::world::object &
sanguis::server::entities::transfer_parameters::world() const
{
	return
		world_;
}

sanguis::collision::world::created const
sanguis::server::entities::transfer_parameters::created() const
{
	return
		created_;
}

sanguis::creator::grid const &
sanguis::server::entities::transfer_parameters::grid() const
{
	return
		grid_;
}

sanguis::server::center const
sanguis::server::entities::transfer_parameters::center() const
{
	return
		center_;
}

sanguis::server::angle const
sanguis::server::entities::transfer_parameters::angle() const
{
	return
		angle_;
}
