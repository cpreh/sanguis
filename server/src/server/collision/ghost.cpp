#include <sanguis/collision/center.hpp>
#include <sanguis/collision/radius.hpp>
#include <sanguis/collision/world/body_enter_container.hpp>
#include <sanguis/collision/world/body_exit_container.hpp>
#include <sanguis/collision/world/ghost.hpp>
#include <sanguis/collision/world/ghost_base_fwd.hpp>
#include <sanguis/collision/world/ghost_group.hpp>
#include <sanguis/collision/world/ghost_parameters.hpp>
#include <sanguis/collision/world/object.hpp>
#include <sanguis/server/radius.hpp>
#include <sanguis/server/collision/ghost.hpp>
#include <fcppt/reference_wrapper_impl.hpp>
#include <fcppt/assert/pre.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


sanguis::server::collision::ghost::ghost(
	sanguis::collision::world::ghost_base &_ghost_base,
	sanguis::collision::world::ghost_group const _collision_group,
	sanguis::server::radius const _radius
)
:
	ghost_base_(
		_ghost_base
	),
	collision_group_(
		_collision_group
	),
	radius_(
		_radius
	),
	impl_()
{
}

sanguis::server::collision::ghost::ghost(
	ghost &&
) = default;

sanguis::server::collision::ghost &
sanguis::server::collision::ghost::operator=(
	ghost &&
) = default;

sanguis::server::collision::ghost::~ghost()
{
}

sanguis::collision::world::body_enter_container
sanguis::server::collision::ghost::transfer(
	sanguis::collision::world::object &_world,
	sanguis::server::center const _center
)
{
	FCPPT_ASSERT_PRE(
		!impl_
	);

	impl_ =
		_world.create_ghost(
			sanguis::collision::world::ghost_parameters(
				sanguis::collision::center(
					_center.get()
				),
				sanguis::collision::radius(
					radius_.get()
				),
				collision_group_,
				ghost_base_.get()
			)
		);

	return
		_world.activate_ghost(
			*impl_
		);
}

sanguis::collision::world::body_exit_container
sanguis::server::collision::ghost::destroy(
	sanguis::collision::world::object &_world
)
{
	FCPPT_ASSERT_PRE(
		impl_
	);

	sanguis::collision::world::body_exit_container result(
		_world.deactivate_ghost(
			*impl_
		)
	);

	impl_.reset();

	return
		std::move(
			result
		);
}

void
sanguis::server::collision::ghost::center(
	sanguis::server::center const _center
)
{
	FCPPT_ASSERT_PRE(
		impl_
	);

	impl_->center(
		sanguis::collision::center(
			_center.get()
		)
	);
}
