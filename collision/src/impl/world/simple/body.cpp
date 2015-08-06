#include <sanguis/collision/center.hpp>
#include <sanguis/collision/mass.hpp>
#include <sanguis/collision/optional_result.hpp>
#include <sanguis/collision/radius.hpp>
#include <sanguis/collision/result.hpp>
#include <sanguis/collision/speed.hpp>
#include <sanguis/collision/impl/duration_to_time.hpp>
#include <sanguis/collision/impl/grid_to_meter.hpp>
#include <sanguis/collision/impl/is_null.hpp>
#include <sanguis/collision/impl/log.hpp>
#include <sanguis/collision/impl/world/simple/body.hpp>
#include <sanguis/collision/impl/world/simple/body_remove_callback.hpp>
#include <sanguis/collision/world/body.hpp>
#include <sanguis/collision/world/body_base.hpp>
#include <sanguis/collision/world/body_group.hpp>
#include <sanguis/collision/world/body_parameters.hpp>
#include <sanguis/creator/size_type.hpp>
#include <sanguis/creator/tile_size.hpp>
#include <fcppt/literal.hpp>
#include <fcppt/maybe_void.hpp>
#include <fcppt/strong_typedef_output.hpp>
#include <fcppt/assert/pre.hpp>
#include <fcppt/log/_.hpp>
#include <fcppt/log/warning.hpp>
#include <fcppt/math/vector/arithmetic.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/units/io.hpp>
#include <fcppt/config/external_end.hpp>


sanguis::collision::impl::world::simple::body::body(
	sanguis::collision::world::body_parameters const &_parameters,
	sanguis::collision::impl::world::simple::body_remove_callback const &_body_remove_callback,
	sanguis::collision::impl::world::simple::body_move_callback const &_body_move_callback
)
:
	sanguis::collision::world::body(),
	body_remove_callback_(
		_body_remove_callback
	),
	body_move_callback_(
		_body_move_callback
	),
	radius_(
		_parameters.radius()
	),
	mass_(
		_parameters.mass()
	),
	collision_group_(
		_parameters.collision_group()
	),
	body_base_(
		_parameters.body_base()
	),
	center_(
		_parameters.center()
	),
	speed_(
		_parameters.speed()
	)
{
	if(
		radius_.get()
		>=
		sanguis::collision::impl::grid_to_meter(
			sanguis::creator::tile_size::value
			/
			fcppt::literal<
				sanguis::creator::size_type
			>(
				2
			)
		)
	)
		FCPPT_LOG_WARNING(
			sanguis::collision::impl::log(),
			fcppt::log::_
				<< FCPPT_TEXT("Body with radius ")
				<< radius_
				<< FCPPT_TEXT(" won't fit into a single tile.")
		);

	FCPPT_ASSERT_PRE(
		!sanguis::collision::impl::is_null(
			_parameters.mass().value()
		)
	);
}

sanguis::collision::impl::world::simple::body::~body()
{
	body_remove_callback_.get()(
		*this
	);
}

void
sanguis::collision::impl::world::simple::body::center(
	sanguis::collision::center const _center
)
{
	center_ =
		_center;

	body_move_callback_.get()(
		*this
	);
}

void
sanguis::collision::impl::world::simple::body::move(
	sanguis::collision::optional_result const &_opt_collision,
	sanguis::collision::duration const _duration
)
{
	fcppt::maybe_void(
		_opt_collision,
		[
			this
		](
			sanguis::collision::result const &_collision
		)
		{

			speed_ =
				_collision.speed();

			this->speed_changed();

			body_base_.world_collision();
		}
	);

	center_ =
		sanguis::collision::center(
			center_.get()
			+
			speed_
			*
			sanguis::collision::impl::duration_to_time(
				_duration
			)
		);

	body_base_.center_changed(
		center_
	);
}

void
sanguis::collision::impl::world::simple::body::push(
	sanguis::collision::result const &_collision
)
{
	speed_ +=
		_collision.speed();

	this->speed_changed();
}

sanguis::collision::center const
sanguis::collision::impl::world::simple::body::center() const
{
	return
		center_;
}

void
sanguis::collision::impl::world::simple::body::speed(
	sanguis::collision::speed const _speed
)
{
	speed_ =
		_speed;
}

sanguis::collision::speed const
sanguis::collision::impl::world::simple::body::speed() const
{
	return
		speed_;
}

sanguis::collision::radius const
sanguis::collision::impl::world::simple::body::radius() const
{
	return
		radius_;
}

sanguis::collision::mass const
sanguis::collision::impl::world::simple::body::mass() const
{
	return
		mass_;
}

sanguis::collision::world::body_group
sanguis::collision::impl::world::simple::body::collision_group() const
{
	return
		collision_group_;
}

sanguis::collision::world::body_base &
sanguis::collision::impl::world::simple::body::body_base() const
{
	return
		body_base_;
}

void
sanguis::collision::impl::world::simple::body::speed_changed()
{
	body_base_.speed_changed(
		speed_
	);
}
