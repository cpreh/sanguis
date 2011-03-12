#include "level_calculate.hpp"
#include "space_unit.hpp"
#include <cmath>

sanguis::server::level_type
sanguis::server::level_calculate(
	exp_type const e,
	level_type
)
{
	return
		level_type(
			static_cast<
				level_type::value_type
			>(
				static_cast<
					space_unit
				>(0.3)
				*
				std::sqrt(
					static_cast<
						space_unit
					>(e)
				)
			)
		);
}
