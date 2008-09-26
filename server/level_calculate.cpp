#include "level_calculate.hpp"
#include <cmath>

sanguis::messages::level_type
sanguis::server::level_calculate(
	messages::exp_type const e,
	messages::level_type)
{
	return static_cast<messages::level_type>(
		std::sqrt(
			static_cast<messages::space_unit>(e)));
}
