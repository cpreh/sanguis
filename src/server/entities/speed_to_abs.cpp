#include "speed_to_abs.hpp"
#include "property/to_float.hpp"
#include <fcppt/math/vector/arithmetic.hpp>
#include <fcppt/math/vector/basic_impl.hpp>
#include <fcppt/math/vector/unit_circle.hpp>

sanguis::server::pos_type const
sanguis::server::entities::speed_to_abs(
	space_unit const direction_,
	property::value const speed_
)
{
	return
		fcppt::math::vector::unit_circle(
			direction_
		)
		*
		property::to_float<
			space_unit
		>(
			speed_
		);
}
