#include <sanguis/collision/center.hpp>
#include <sanguis/collision/radius.hpp>
#include <sanguis/collision/world/ghost_base_fwd.hpp>
#include <sanguis/collision/world/ghost_base_ref.hpp>
#include <sanguis/collision/world/ghost_group.hpp>
#include <sanguis/collision/world/ghost_parameters.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


sanguis::collision::world::ghost_parameters::ghost_parameters(
	sanguis::collision::center _center,
	sanguis::collision::radius _radius,
	sanguis::collision::world::ghost_group const _collision_group,
	sanguis::collision::world::ghost_base_ref const _ghost_base
)
:
	center_(
		std::move(
			_center
		)
	),
	radius_(
		std::move(
			_radius
		)
	),
	collision_group_(
		_collision_group
	),
	ghost_base_(
		_ghost_base
	)
{
}

sanguis::collision::center
sanguis::collision::world::ghost_parameters::center() const
{
	return
		center_;
}

sanguis::collision::radius
sanguis::collision::world::ghost_parameters::radius() const
{
	return
		radius_;
}

sanguis::collision::world::ghost_group
sanguis::collision::world::ghost_parameters::collision_group() const
{
	return
		collision_group_;
}

sanguis::collision::world::ghost_base &
sanguis::collision::world::ghost_parameters::ghost_base() const
{
	return
		ghost_base_.get();
}
