#include "level_calculate.hpp"
#include "space_unit.hpp"
#include <cmath>

sanguis::server::level const
sanguis::server::level_calculate(
	server::exp const _exp,
	server::level
)
{
	return
		server::level(
			static_cast<
				server::level::value_type
			>(
				static_cast<
					server::space_unit
				>(
					0.3
				)
				*
				std::sqrt(
					static_cast<
						server::space_unit
					>(
						_exp.get()
					)
				)
			)
		);
}
