#include <sanguis/server/space_unit.hpp>
#include <sanguis/server/entities/speed_to_abs.hpp>
#include <sanguis/server/entities/property/to_float.hpp>
#include <fcppt/math/vector/arithmetic.hpp>
#include <fcppt/math/vector/basic_impl.hpp>
#include <fcppt/math/vector/hypersphere_to_cartesian.hpp>
#include <fcppt/math/vector/static.hpp>

sanguis::server::speed const
sanguis::server::entities::speed_to_abs(
	server::direction const _direction,
	property::value const _speed
)
{
	return
		server::speed(
			fcppt::math::vector::hypersphere_to_cartesian(
				fcppt::math::vector::static_<
					server::space_unit,
					1
				>::type(
					_direction.get()
				)
			)
			*
			property::to_float<
				server::space_unit
			>(
				_speed
			)
		);
}
