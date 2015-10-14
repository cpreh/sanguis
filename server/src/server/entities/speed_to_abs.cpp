#include <sanguis/server/direction.hpp>
#include <sanguis/server/space_unit.hpp>
#include <sanguis/server/speed.hpp>
#include <sanguis/server/entities/speed_to_abs.hpp>
#include <sanguis/server/entities/property/value.hpp>
#include <fcppt/cast/size.hpp>
#include <fcppt/math/vector/arithmetic.hpp>
#include <fcppt/math/vector/hypersphere_to_cartesian.hpp>
#include <fcppt/math/vector/static.hpp>


sanguis::server::speed
sanguis::server::entities::speed_to_abs(
	sanguis::server::direction const _direction,
	sanguis::server::entities::property::value const _speed
)
{
	return
		sanguis::server::speed(
			fcppt::math::vector::hypersphere_to_cartesian(
				fcppt::math::vector::static_<
					sanguis::server::space_unit,
					1
				>(
					_direction.get()
				)
			)
			*
			fcppt::cast::size<
				sanguis::server::space_unit
			>(
				_speed
			)
		);
}
