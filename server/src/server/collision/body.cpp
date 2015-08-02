#include <sanguis/collision/world/body.hpp>
#include <sanguis/collision/world/body_enter_container.hpp>
#include <sanguis/collision/world/body_exit_container.hpp>
#include <sanguis/collision/world/body_group.hpp>
#include <sanguis/collision/world/body_parameters.hpp>
#include <sanguis/collision/world/body_unique_ptr.hpp>
#include <sanguis/collision/world/created.hpp>
#include <sanguis/collision/world/object.hpp>
#include <sanguis/server/center.hpp>
#include <sanguis/server/radius.hpp>
#include <sanguis/server/speed.hpp>
#include <sanguis/server/collision/body.hpp>
#include <sanguis/server/collision/from_center.hpp>
#include <sanguis/server/collision/from_speed.hpp>
#include <sanguis/server/collision/to_center.hpp>
#include <sanguis/server/collision/to_radius.hpp>
#include <sanguis/server/collision/to_speed.hpp>
#include <fcppt/optional_assign.hpp>
#include <fcppt/optional_impl.hpp>
#include <fcppt/assert/optional_error.hpp>
#include <fcppt/assert/pre.hpp>


sanguis::server::collision::body::body(
	sanguis::server::radius const _radius,
	sanguis::collision::world::body_base &_body_base
)
:
	radius_(
		_radius
	),
	body_base_(
		_body_base
	),
	body_()
{
}

sanguis::server::collision::body::~body()
{
}

void
sanguis::server::collision::body::center(
	sanguis::server::center const _center
)
{
	FCPPT_ASSERT_OPTIONAL_ERROR(
		body_
	)->center(
		sanguis::server::collision::to_center(
			_center
		)
	);
}

sanguis::server::center const
sanguis::server::collision::body::center() const
{
	return
		sanguis::server::collision::from_center(
			FCPPT_ASSERT_OPTIONAL_ERROR(
				body_
			)->center()
		);
}

void
sanguis::server::collision::body::speed(
	sanguis::server::speed const _speed
)
{
	FCPPT_ASSERT_OPTIONAL_ERROR(
		body_
	)->speed(
		sanguis::server::collision::to_speed(
			_speed
		)
	);
}

sanguis::server::speed const
sanguis::server::collision::body::speed() const
{
	return
		sanguis::server::collision::from_speed(
			FCPPT_ASSERT_OPTIONAL_ERROR(
				body_
			)->speed()
		);
}

sanguis::server::radius const
sanguis::server::collision::body::radius() const
{
	return
		radius_;
}

sanguis::collision::world::body_enter_container
sanguis::server::collision::body::transfer(
	sanguis::collision::world::object &_world,
	sanguis::collision::world::created const _created,
	sanguis::server::center const _center,
	sanguis::server::speed const _speed,
	sanguis::collision::world::body_group const _collision_group
)
{
	FCPPT_ASSERT_PRE(
		!body_.has_value()
	);

	sanguis::collision::world::body_unique_ptr const &new_body(
		fcppt::optional_assign(
			body_,
			_world.create_body(
				sanguis::collision::world::body_parameters(
					sanguis::server::collision::to_center(
						_center
					),
					sanguis::server::collision::to_speed(
						_speed
					),
					sanguis::server::collision::to_radius(
						radius_
					),
					_collision_group,
					body_base_
				)
			)
		)
	);

	return
		_world.activate_body(
			*new_body,
			_created
		);
}

sanguis::collision::world::body_exit_container
sanguis::server::collision::body::remove(
	sanguis::collision::world::object &_world
)
{
	sanguis::collision::world::body_exit_container result(
		_world.deactivate_body(
			*FCPPT_ASSERT_OPTIONAL_ERROR(
				body_
			)
		)
	);

	body_ =
		optional_body_unique_ptr();

	return
		result;
}
