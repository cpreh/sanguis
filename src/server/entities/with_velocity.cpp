#include <sanguis/server/entities/with_velocity.hpp>
#include <sanguis/server/entities/speed_to_abs.hpp>
#include <fcppt/math/vector/object_impl.hpp>
#include <fcppt/tr1/functional.hpp>

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

void
sanguis::server::entities::with_velocity::direction(
	server::direction const _direction
)
{
	direction_ = _direction;

	this->speed_change(
		movement_speed_.current()
	);
}

sanguis::server::speed const
sanguis::server::entities::with_velocity::abs_speed() const
{
	return
		entities::speed_to_abs(
			direction_,
			movement_speed_.current()
		);
}

sanguis::server::entities::with_velocity::~with_velocity()
{
}

sanguis::server::entities::with_velocity::with_velocity(
	property::initial const &_movement_speed,
	server::direction const _direction
)
:
	entities::base(),
	movement_speed_(
		_movement_speed
	),
	direction_(
		_direction
	),
	speed_change_(
		movement_speed_.register_change_callback(
			std::tr1::bind(
				&with_velocity::speed_change,
				this,
				std::tr1::placeholders::_1
			)
		)
	)
{
}

void
sanguis::server::entities::with_velocity::speed_change(
	property::value const _speed
)
{
	this->on_speed_change(
		entities::speed_to_abs(
			this->direction(),
			_speed
		)
	);
}

sanguis::server::speed const
sanguis::server::entities::with_velocity::initial_abs_speed() const
{
	return
		this->abs_speed();
}
