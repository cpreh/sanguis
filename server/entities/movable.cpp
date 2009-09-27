#include "movable.hpp"
#include "../../angle_to_vector.hpp"
#include <sge/math/vector/basic_impl.hpp>
#include <sge/math/vector/arithmetic.hpp>
#include <boost/bind.hpp>

sanguis::server::entities::property &
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
		direction_
	);
}

sanguis::server::pos_type const
sanguis::server::entities::movable::abs_speed() const
{
	return
		angle_to_vector(
			direction_
		)
		* movement_speed_.current();
}

sanguis::server::entities::movable::movable(
	property const &nmovement_speed_,
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
			boost::bind(
				&movable::speed_change,
				this,
				_1
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
	property::value_type const s
)
{
	body_speed(
		angle_to_vector(
			direction()
		) * s
	);
}
