#include <sanguis/server/direction.hpp>
#include <sanguis/server/speed.hpp>
#include <sanguis/server/entities/base.hpp>
#include <sanguis/server/entities/speed_to_abs.hpp>
#include <sanguis/server/entities/with_velocity.hpp>
#include <sanguis/server/entities/ifaces/with_id.hpp>
#include <sanguis/server/entities/ifaces/with_velocity.hpp>
#include <sanguis/server/entities/property/changeable.hpp>
#include <sanguis/server/entities/property/initial_fwd.hpp>
#include <sanguis/server/entities/property/value.hpp>
#include <fcppt/config/external_begin.hpp>
#include <functional>
#include <fcppt/config/external_end.hpp>


sanguis::server::entities::with_velocity::with_velocity(
	sanguis::server::entities::property::initial const &_movement_speed,
	sanguis::server::direction const _direction
)
:
	sanguis::server::entities::base(),
	sanguis::server::entities::ifaces::with_id(),
	sanguis::server::entities::ifaces::with_velocity(),
	movement_speed_(
		_movement_speed
	),
	direction_(
		_direction
	),
	speed_change_(
		movement_speed_.register_change_callback(
			std::bind(
				&sanguis::server::entities::with_velocity::speed_change,
				this,
				std::placeholders::_1
			)
		)
	)
{
}

sanguis::server::entities::with_velocity::~with_velocity()
{
}

sanguis::server::entities::property::changeable &
sanguis::server::entities::with_velocity::movement_speed()
{
	return movement_speed_;
}

sanguis::server::direction const
sanguis::server::entities::with_velocity::direction() const
{
	return direction_;
}

sanguis::server::speed const
sanguis::server::entities::with_velocity::speed() const
{
	return
		this->actual_speed();
}

void
sanguis::server::entities::with_velocity::speed(
	sanguis::server::speed const _speed
)
{
	this->on_speed_change(
		_speed
	);
}

void
sanguis::server::entities::with_velocity::direction(
	sanguis::server::direction const _direction
)
{
	direction_ = _direction;

	this->speed_change(
		movement_speed_.current()
	);
}

void
sanguis::server::entities::with_velocity::speed_change(
	sanguis::server::entities::property::value const _speed
)
{
	this->on_speed_change(
		sanguis::server::entities::speed_to_abs(
			this->direction(),
			_speed
		)
	);
}

sanguis::server::speed const
sanguis::server::entities::with_velocity::initial_abs_speed() const
{
	return
		sanguis::server::entities::speed_to_abs(
			direction_,
			movement_speed_.current()
		);
}
