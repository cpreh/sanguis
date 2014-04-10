#include <sanguis/server/center.hpp>
#include <sanguis/server/speed.hpp>
#include <sanguis/server/collision/result.hpp>


sanguis::server::collision::result::result(
	sanguis::server::speed const &_speed,
	sanguis::server::center const &_center
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

sanguis::server::speed const &
sanguis::server::collision::result::speed() const
{
	return
		speed_;
}

sanguis::server::center const &
sanguis::server::collision::result::center() const
{
	return
		center_;
}
