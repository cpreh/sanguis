#include "speed_to_abs.hpp"
#include "property/to_float.hpp"
#include "../../angle_to_vector.hpp"
#include <sge/math/vector/arithmetic.hpp>
#include <sge/math/vector/basic_impl.hpp>

sanguis::server::pos_type const
sanguis::server::entities::speed_to_abs(
	space_unit const direction_,
	property::value const speed_
)
{
	return
		angle_to_vector(
			direction_
		)
		*
		property::to_float<
			space_unit
		>(
			speed_
		);
}
