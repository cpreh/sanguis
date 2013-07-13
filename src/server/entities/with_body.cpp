#include <sanguis/duration_second.hpp>
#include <sanguis/server/angle.hpp>
#include <sanguis/server/center.hpp>
#include <sanguis/server/radius.hpp>
#include <sanguis/server/speed.hpp>
#include <sanguis/server/collision/body_base.hpp>
#include <sanguis/server/collision/body.hpp>
#include <sanguis/server/collision/make_groups.hpp>
#include <sanguis/server/collision/optional_result.hpp>
#include <sanguis/server/collision/result.hpp>
#include <sanguis/server/collision/user_data.hpp>
#include <sanguis/server/collision/with_world.hpp>
#include <sanguis/server/entities/body_parameters.hpp>
#include <sanguis/server/entities/transfer_parameters.hpp>
#include <sanguis/server/entities/with_body.hpp>
#include <sanguis/server/entities/with_ghosts.hpp>
#include <sanguis/server/entities/ifaces/with_angle.hpp>
#include <sanguis/server/entities/ifaces/with_body.hpp>
#include <sanguis/server/entities/ifaces/with_id.hpp>
#include <sge/projectile/world.hpp>
#include <sge/projectile/body/scoped.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/try_dynamic_cast.hpp>
#include <fcppt/assert/pre.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/logic/tribool.hpp>
#include <functional>
#include <fcppt/config/external_end.hpp>


sanguis::server::entities::with_body::with_body(
	sanguis::server::entities::body_parameters const &_params
)
:
	sanguis::server::entities::with_ghosts(),
	sanguis::server::entities::ifaces::with_body(),
	sanguis::server::entities::ifaces::with_angle(),
	sanguis::server::entities::ifaces::with_id(),
	sanguis::server::collision::body_base(),
	radius_(
		_params.radius()
	),
	collision_body_(
		fcppt::make_unique_ptr<
			sanguis::server::collision::body
		>(
			sanguis::server::center(
				sanguis::server::center::value_type::null()
			),
			sanguis::server::speed(
				sanguis::server::speed::value_type::null()
			),
			sanguis::server::angle(
				0.f
			),
			_params.radius(),
			_params.solidity(),
			sanguis::server::collision::user_data(
				*this
			),
			std::bind(
				&sanguis::server::entities::with_body::on_position_change,
				this,
				std::placeholders::_1
			)
		)
	),
	scoped_body_()
{
}

sanguis::server::entities::with_body::~with_body()
{
	FCPPT_ASSERT_PRE(
		!scoped_body_
	);
}

sanguis::server::center const
sanguis::server::entities::with_body::center() const
{
	return
		collision_body_->center();
}

void
sanguis::server::entities::with_body::world_collision(
	sanguis::server::collision::result const &_result
)
{
	// TODO: Use the position as well?
	this->reset_speed(
		_result.speed()
	);
}

sanguis::server::angle const
sanguis::server::entities::with_body::angle() const
{
	return
		collision_body_->angle();
}

void
sanguis::server::entities::with_body::center(
	sanguis::server::center const &_center
)
{
	collision_body_->center(
		_center
	);
}

void
sanguis::server::entities::with_body::angle(
	sanguis::server::angle const _angle
)
{
	collision_body_->angle(
		_angle
	);
}

sanguis::server::radius const
sanguis::server::entities::with_body::radius() const
{
	return
		radius_;
}

bool
sanguis::server::entities::with_body::on_transfer(
	sanguis::server::entities::transfer_parameters const &_params
)
{
	collision_body_->angle(
		_params.angle()
	);

	collision_body_->center(
		_params.center()
	);

	// Do this before we get a speed != 0
	if(
		sanguis::server::collision::with_world(
			*this,
			_params.grid(),
			sanguis::duration_second(
				0
			)
		)
	)
		return false;

	collision_body_->speed(
		this->initial_speed()
	);

	scoped_body_.take(
		fcppt::make_unique_ptr<
			sge::projectile::body::scoped
		>(
			_params.world(),
			collision_body_->get(),
			sanguis::server::collision::make_groups(
				this->collision_groups(),
				_params.global_groups()
			)
		)
	);

	return
		sanguis::server::entities::with_ghosts::on_transfer(
			_params
		);
}

void
sanguis::server::entities::with_body::on_destroy()
{
	scoped_body_.reset();

	sanguis::server::entities::with_ghosts::on_destroy();
}

void
sanguis::server::entities::with_body::on_position_change(
	sanguis::server::center const &_center
)
{
	sanguis::server::entities::with_ghosts::update_center(
		_center
	);
}

boost::logic::tribool const
sanguis::server::entities::with_body::can_collide_with(
	sanguis::server::collision::body_base const &_body_base
) const
{
	FCPPT_TRY_DYNAMIC_CAST(
		sanguis::server::entities::with_body const *,
		entity,
		&_body_base
	)
		return
			this->can_collide_with_body(
				*entity
			);

	return boost::logic::indeterminate;
}

void
sanguis::server::entities::with_body::collision(
	sanguis::server::collision::body_base &_body_base
)
{
	FCPPT_TRY_DYNAMIC_CAST(
		sanguis::server::entities::with_body *,
		entity,
		&_body_base
	)
		this->collision_with_body(
			*entity
		);
}

boost::logic::tribool const
sanguis::server::entities::with_body::can_collide_with_body(
	sanguis::server::entities::with_body const &
) const
{
	return boost::logic::indeterminate;
}

void
sanguis::server::entities::with_body::collision_with_body(
	sanguis::server::entities::with_body &
)
{
}

void
sanguis::server::entities::with_body::reset_speed(
	sanguis::server::speed const &_speed
)
{
	collision_body_->speed(
		_speed
	);
}

sanguis::server::speed const
sanguis::server::entities::with_body::body_speed() const
{
	return
		collision_body_->speed();
}
