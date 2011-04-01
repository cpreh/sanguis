#include "movable.hpp"
#include "speed_to_abs.hpp"
#include <fcppt/math/vector/basic_impl.hpp>
#include <fcppt/tr1/functional.hpp>

sanguis::server::entities::property::changeable &
sanguis::server::entities::movable::movement_speed()
{
	return movement_speed_;
}

sanguis::server::direction const
sanguis::server::entities::movable::direction() const
{
	return direction_;
}

void
sanguis::server::entities::movable::direction(
	server::direction const _direction
)
{
	direction_ = _direction;

	this->speed_change(
		movement_speed_.current()
	);
}

sanguis::server::speed const
sanguis::server::entities::movable::abs_speed() const
{
	return
		entities::speed_to_abs(
			direction_,
			movement_speed_.current()
		);
}

sanguis::server::entities::movable::~movable()
{
}

sanguis::server::entities::movable::movable(
	property::initial const &_movement_speed,
	server::direction const _direction
)
:
	entities::with_body(),
	movement_speed_(
		_movement_speed
	),
	direction_(
		_direction
	),
	speed_change_(
		movement_speed_.register_change_callback(
			std::tr1::bind(
				&movable::speed_change,
				this,
				std::tr1::placeholders::_1
			)
		)
	)
{
}

sanguis::server::speed const
sanguis::server::entities::movable::initial_direction() const
{
	return this->abs_speed();
}

void
sanguis::server::entities::movable::speed_change(
	property::value const _speed
)
{
	this->speed(
		entities::speed_to_abs(
			this->direction(),
			_speed
		)
	);
}
