#include <sanguis/collision/result.hpp>
#include <sanguis/collision/speed.hpp>


sanguis::collision::result::result(
	sanguis::collision::speed const _speed
)
:
	speed_(
		_speed
	)
{
}

sanguis::collision::speed
sanguis::collision::result::speed() const
{
	return
		speed_;
}
