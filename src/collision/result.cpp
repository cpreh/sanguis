#include <sanguis/collision/center.hpp>
#include <sanguis/collision/result.hpp>
#include <sanguis/collision/speed.hpp>


sanguis::collision::result::result(
	sanguis::collision::speed const &_speed,
	sanguis::collision::center const &_center
)
:
	speed_(
		_speed
	),
	center_(
		_center
	)
{
}

sanguis::collision::speed const &
sanguis::collision::result::speed() const
{
	return
		speed_;
}

sanguis::collision::center const &
sanguis::collision::result::center() const
{
	return
		center_;
}
