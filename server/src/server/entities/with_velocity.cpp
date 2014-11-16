#include <sanguis/server/direction.hpp>
#include <sanguis/server/model_size.hpp>
#include <sanguis/server/speed.hpp>
#include <sanguis/server/collision/optional_result.hpp>
#include <sanguis/server/collision/with_world_move.hpp>
#include <sanguis/server/entities/base.hpp>
#include <sanguis/server/entities/movement_speed.hpp>
#include <sanguis/server/entities/movement_speed_initial.hpp>
#include <sanguis/server/entities/speed_to_abs.hpp>
#include <sanguis/server/entities/transfer_parameters_fwd.hpp>
#include <sanguis/server/entities/with_body.hpp>
#include <sanguis/server/entities/with_velocity.hpp>
#include <sanguis/server/entities/ifaces/with_id.hpp>
#include <sanguis/server/entities/ifaces/with_velocity.hpp>
#include <sanguis/server/entities/property/changeable.hpp>
#include <sanguis/server/environment/object.hpp>
#include <fcppt/config/external_begin.hpp>
#include <functional>
#include <fcppt/config/external_end.hpp>


sanguis::server::entities::with_velocity::with_velocity(
	sanguis::server::model_size const _model_size,
	sanguis::server::entities::movement_speed_initial const _movement_speed,
	sanguis::server::direction const _direction
)
:
	sanguis::server::entities::ifaces::with_id(),
	sanguis::server::entities::ifaces::with_velocity(),
	sanguis::server::entities::with_body(
		_model_size
	),
	movement_speed_(
		_movement_speed.get()
	),
	direction_(
		_direction
	),
	net_center_(
		this->diff_clock()
	),
	net_speed_(
		this->diff_clock()
	),
	speed_change_(
		movement_speed_.register_change_callback(
			std::bind(
				&sanguis::server::entities::with_velocity::desired_speed_change,
				this
			)
		)
	)
{
}

void
sanguis::server::entities::with_velocity::update()
{
	sanguis::server::entities::with_body::update();

	if(
		net_center_.update()
	)
		this->environment()->center_changed(
			this->id(),
			this->center()
		);

	if(
		net_speed_.update()
	)
		this->environment()->speed_changed(
			this->id(),
			this->speed()
		);
}

bool
sanguis::server::entities::with_velocity::on_transfer(
	sanguis::server::entities::transfer_parameters const &_parameters
)
{
	net_center_.reset();

	net_speed_.reset();

	return
		sanguis::server::entities::with_body::on_transfer(
			_parameters
		);
}

sanguis::server::entities::with_velocity::~with_velocity()
{
}

void
sanguis::server::entities::with_velocity::world_collision(
	sanguis::creator::grid const &_grid,
	sanguis::duration const _duration
)
{
	sanguis::server::collision::optional_result const result(
		sanguis::server::collision::with_world_move(
			*this,
			_grid,
			_duration
		)
	);

	if(
		result
	)
		this->on_world_collision(
			*result
		);
}

sanguis::server::entities::property::changeable &
sanguis::server::entities::with_velocity::movement_speed()
{
	return
		movement_speed_;
}

sanguis::server::entities::movement_speed const
sanguis::server::entities::with_velocity::max_movement_speed() const
{
	return
		sanguis::server::entities::movement_speed{
			movement_speed_.max()
		};
}

sanguis::server::direction const
sanguis::server::entities::with_velocity::direction() const
{
	return
		direction_;
}

void
sanguis::server::entities::with_velocity::direction(
	sanguis::server::direction const _direction
)
{
	direction_ = _direction;

	this->desired_speed_change();
}

sanguis::server::speed const
sanguis::server::entities::with_velocity::speed() const
{
	return
		this->body_speed();
}

void
sanguis::server::entities::with_velocity::desired_speed_change()
{
	this->body_speed(
		this->desired_speed()
	);
}

void
sanguis::server::entities::with_velocity::on_position_change(
	sanguis::server::center const _center
)
{
	net_center_.set(
		_center
	);
}

void
sanguis::server::entities::with_velocity::on_speed_change(
	sanguis::server::speed const _speed
)
{
	net_speed_.set(
		_speed
	);
}

sanguis::server::speed const
sanguis::server::entities::with_velocity::desired_speed() const
{
	return
		sanguis::server::entities::speed_to_abs(
			this->direction(),
			movement_speed_.current()
		);
}

sanguis::server::speed const
sanguis::server::entities::with_velocity::initial_speed() const
{
	return
		this->desired_speed();
}
