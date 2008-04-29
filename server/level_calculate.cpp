#include "level_calculate.hpp"
#include <cmath>

sanguis::messages::level_type sanguis::server::level_calculate(const messages::exp_type e,const messages::level_type)
{
	return static_cast<messages::level_type>(std::sqrt(static_cast<messages::exp_type>(e)));
}
