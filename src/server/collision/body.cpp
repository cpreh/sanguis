#include <sanguis/collision/center.hpp>
#include <sanguis/collision/speed.hpp>
#include <sanguis/collision/world/body.hpp>
#include <sanguis/collision/world/body_parameters.hpp>
#include <sanguis/collision/world/group_field.hpp>
#include <sanguis/collision/world/object.hpp>
#include <sanguis/collision/world/position_change_callback.hpp>
#include <sanguis/server/center.hpp>
#include <sanguis/server/radius.hpp>
#include <sanguis/server/speed.hpp>
#include <sanguis/server/collision/body.hpp>
#include <sanguis/server/collision/position_callback.hpp>
#include <fcppt/assert/pre.hpp>


sanguis::server::collision::body::body(
	sanguis::server::radius const _radius,
	sanguis::collision::world::body_base &_body_base,
	sanguis::server::collision::position_callback const &_position_callback
)
:
	radius_(
		_radius
	),
	body_base_(
		_body_base
	),
	position_callback_(
		_position_callback
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
	FCPPT_ASSERT_PRE(
		body_
	);

	body_->center(
		sanguis::collision::center(
			_center.get()
		)
	);
}

sanguis::server::center const
sanguis::server::collision::body::center() const
{
	FCPPT_ASSERT_PRE(
		body_
	);

	return
		sanguis::server::center(
			body_->center().get()
		);
}

void
sanguis::server::collision::body::speed(
	sanguis::server::speed const _speed
)
{
	FCPPT_ASSERT_PRE(
		body_
	);

	body_->speed(
		sanguis::collision::speed(
			_speed.get()
		)
	);
}

sanguis::server::speed const
sanguis::server::collision::body::speed() const
{
	FCPPT_ASSERT_PRE(
		body_
	);

	return
		sanguis::server::speed(
			body_->speed().get()
		);
}

sanguis::server::radius const
sanguis::server::collision::body::radius() const
{
	return
		radius_;
}

void
sanguis::server::collision::body::transfer(
	sanguis::collision::world::object &_world,
	sanguis::server::center const _center,
	sanguis::server::speed const _speed,
	sanguis::collision::world::group_field const &_collision_groups
)
{
	this->destroy();

	body_.take(
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
				sanguis::collision::world::position_change_callback(
					[
						this
					](
						sanguis::collision::center const _new_center
					)
					{
						position_callback_(
							sanguis::server::center(
								_new_center.get()
							)
						);
					}
				),
				_collision_groups,
				body_base_
			)
		)
	);

	_world.activate_body(
		*body_
	);
}

void
sanguis::server::collision::body::destroy()
{
	body_.reset();
}
