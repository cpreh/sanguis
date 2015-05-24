#include <sanguis/collision/center.hpp>
#include <sanguis/collision/speed.hpp>
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
#include <fcppt/optional_impl.hpp>
#include <fcppt/assert/optional_error.hpp>
#include <fcppt/assert/pre.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


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
		sanguis::collision::center(
			_center.get()
		)
	);
}

sanguis::server::center const
sanguis::server::collision::body::center() const
{
	return
		sanguis::server::center(
			FCPPT_ASSERT_OPTIONAL_ERROR(
				body_
			)->center().get()
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
		sanguis::collision::speed(
			_speed.get()
		)
	);
}

sanguis::server::speed const
sanguis::server::collision::body::speed() const
{
	return
		sanguis::server::speed(
			FCPPT_ASSERT_OPTIONAL_ERROR(
				body_
			)->speed().get()
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

	// TODO: Improve this
	sanguis::collision::world::body_unique_ptr new_body(
		_world.create_body(
			sanguis::collision::world::body_parameters(
				sanguis::collision::center(
					_center.get()
				),
				sanguis::collision::speed(
					_speed.get()
				),
				sanguis::collision::radius(
					radius_.get()
				),
				_collision_group,
				body_base_
			)
		)
	);

	sanguis::collision::world::body &body_ref(
		*new_body
	);

	body_ =
		optional_body_unique_ptr(
			std::move(
				new_body
			)
		);

	return
		_world.activate_body(
			body_ref,
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
