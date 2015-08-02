#include <sanguis/collision/speed.hpp>
#include <sanguis/server/space_unit.hpp>
#include <sanguis/server/speed.hpp>
#include <sanguis/server/collision/to_speed.hpp>
#include <fcppt/math/vector/map.hpp>
#include <boost/units/systems/si/velocity.hpp>


sanguis::collision::speed const
sanguis::server::collision::to_speed(
	sanguis::server::speed const _speed
)
{
	return
		fcppt::math::vector::map(
			_speed.get(),
			[](
				sanguis::server::space_unit const _value
			)
			{
				return
					_value
					*
					boost::units::si::meter_per_second;
			}
		);
}
