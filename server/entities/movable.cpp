#include "movable.hpp"
#include "speed_to_abs.hpp"
#include <sge/math/vector/basic_impl.hpp>
#include <tr1/functional>

sanguis::server::entities::property::changeable &
sanguis::server::entities::movable::movement_speed()
{
	return movement_speed_;
}

sanguis::server::space_unit
sanguis::server::entities::movable::direction() const
{
	return direction_;
}

void
sanguis::server::entities::movable::direction(
	space_unit const ndirection_
)
{
	direction_ = ndirection_;

	speed_change(
		movement_speed_.current()
	);
}

sanguis::server::pos_type const
sanguis::server::entities::movable::abs_speed() const
{
	return
		speed_to_abs(
			direction_,
			movement_speed_.current()
		);
}

sanguis::server::entities::movable::movable(
	property::initial const &nmovement_speed_,
	space_unit const direction_
)
:
	movement_speed_(
		nmovement_speed_
	),
	direction_(
		direction_
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
{}

sanguis::server::pos_type const
sanguis::server::entities::movable::initial_direction() const
{
	return abs_speed();
}

void
sanguis::server::entities::movable::speed_change(
	property::value const s
)
{
	body_speed(
		speed_to_abs(
			direction(),
			s
		)
	);
}
