#include "level_calculate.hpp"
#include "space_unit.hpp"
#include <cmath>

sanguis::server::level_type
sanguis::server::level_calculate(
	exp_type const e,
	level_type)
{
	return static_cast<level_type>(
		std::sqrt(
			static_cast<space_unit>(e)
		)
	);
}
