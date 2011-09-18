#include <sanguis/server/entities/speed_to_abs.hpp>
#include <sanguis/server/entities/property/to_float.hpp>
#include <fcppt/math/vector/arithmetic.hpp>
#include <fcppt/math/vector/basic_impl.hpp>
#include <fcppt/math/vector/unit_circle.hpp>

sanguis::server::speed const
sanguis::server::entities::speed_to_abs(
	server::direction const _direction,
	property::value const _speed
)
{
	return
		server::speed(
			fcppt::math::vector::unit_circle(
				_direction.get()
			)
			*
			property::to_float<
				server::space_unit
			>(
				_speed
			)
		);
}
