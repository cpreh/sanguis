#include <sanguis/diff_clock_fwd.hpp>
#include <sanguis/collision/world/body_base.hpp>
#include <sanguis/collision/world/group_field.hpp>
#include <sanguis/server/angle.hpp>
#include <sanguis/server/center.hpp>
#include <sanguis/server/dim.hpp>
#include <sanguis/server/radius.hpp>
#include <sanguis/server/space_unit.hpp>
#include <sanguis/server/speed.hpp>
#include <sanguis/server/collision/body.hpp>
#include <sanguis/server/collision/position_callback.hpp>
#include <sanguis/server/collision/result.hpp>
#include <sanguis/server/entities/check_dim.hpp>
#include <sanguis/server/entities/radius.hpp>
#include <sanguis/server/entities/transfer_parameters.hpp>
#include <sanguis/server/entities/with_body.hpp>
#include <sanguis/server/entities/with_ghosts.hpp>
#include <sanguis/server/entities/ifaces/with_angle.hpp>
#include <sanguis/server/entities/ifaces/with_id.hpp>
#include <sanguis/server/entities/ifaces/with_links.hpp>
#include <sanguis/server/environment/object.hpp>
#include <fcppt/literal.hpp>
#include <fcppt/try_dynamic_cast.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/logic/tribool.hpp>
#include <functional>
#include <fcppt/config/external_end.hpp>


sanguis::server::entities::with_body::with_body(
	sanguis::diff_clock const &_diff_clock,
	sanguis::server::dim const _dim
)
:
	sanguis::server::entities::with_ghosts(),
	sanguis::server::entities::ifaces::with_angle(),
	sanguis::server::entities::ifaces::with_id(),
	sanguis::server::entities::ifaces::with_links(),
	sanguis::collision::world::body_base(),
	dim_(
		sanguis::server::entities::check_dim(
			_dim
		)
	),
	angle_(
		fcppt::literal<
			sanguis::server::space_unit
		>(
			0
		)
	),
	collision_body_(
		sanguis::server::entities::radius(
			dim_
		),
		*this,
		sanguis::server::collision::position_callback(
			std::bind(
				&sanguis::server::entities::with_body::position_change,
				this,
				std::placeholders::_1
			)
		)
		// TODO: Put the collision groups here!
	),
	net_angle_(
		_diff_clock
	)
{
}

sanguis::server::entities::with_body::~with_body()
{
}

sanguis::server::center const
sanguis::server::entities::with_body::center() const
{
	return
		collision_body_.center();
}

sanguis::server::angle const
sanguis::server::entities::with_body::angle() const
{
	return
		angle_;
}

void
sanguis::server::entities::with_body::center(
	sanguis::server::center const &_center
)
{
	collision_body_.center(
		_center
	);
}

void
sanguis::server::entities::with_body::angle(
	sanguis::server::angle const _angle
)
{
	angle_ =
		_angle;

	net_angle_.set(
		angle_
	);
}

sanguis::server::radius const
sanguis::server::entities::with_body::radius() const
{
	return
		collision_body_.radius();
}

sanguis::server::dim const
sanguis::server::entities::with_body::dim() const
{
	return
		dim_;
}

bool
sanguis::server::entities::with_body::on_transfer(
	sanguis::server::entities::transfer_parameters const &_parameters
)
{
	net_angle_.reset();

	this->angle(
		_parameters.angle()
	);

	collision_body_.transfer(
		_parameters.world(),
		_parameters.center(),
		this->initial_speed(),
		this->collision_groups()
	);

	return
		sanguis::server::entities::with_ghosts::on_transfer(
			_parameters
		);
}

void
sanguis::server::entities::with_body::update()
{
	if(
		net_angle_.update()
	)
		this->environment().angle_changed(
			this->id(),
			this->angle()
		);
}

void
sanguis::server::entities::with_body::on_world_collision(
	sanguis::server::collision::result const &_result
)
{
	this->center(
		_result.center()
	);

	this->body_speed(
		_result.speed()
	);
}

void
sanguis::server::entities::with_body::destroy()
{
	// TODO: Is this still needed?
	collision_body_.destroy();

	sanguis::server::entities::with_ghosts::destroy();
}

void
sanguis::server::entities::with_body::body_speed(
	sanguis::server::speed const _speed
)
{
	collision_body_.speed(
		_speed
	);

	this->on_speed_change(
		_speed
	);
}

sanguis::server::speed const
sanguis::server::entities::with_body::body_speed() const
{
	return
		collision_body_.speed();
}

boost::logic::tribool const
sanguis::server::entities::with_body::can_collide_with(
	sanguis::collision::world::body_base const &_body_base
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

	return
		boost::logic::indeterminate;
}

void
sanguis::server::entities::with_body::collision(
	sanguis::collision::world::body_base &_body_base
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
	return
		boost::logic::indeterminate;
}

void
sanguis::server::entities::with_body::collision_with_body(
	sanguis::server::entities::with_body &
)
{
}

sanguis::server::speed const
sanguis::server::entities::with_body::initial_speed() const
{
	return
		sanguis::server::speed(
			sanguis::server::speed::value_type::null()
		);
}

void
sanguis::server::entities::with_body::position_change(
	sanguis::server::center const _center
)
{
	this->sanguis::server::entities::with_ghosts::update_center(
		_center
	);

	this->on_position_change(
		_center
	);
}

void
sanguis::server::entities::with_body::on_position_change(
	sanguis::server::center
)
{
}

void
sanguis::server::entities::with_body::on_speed_change(
	sanguis::server::speed
)
{
}
