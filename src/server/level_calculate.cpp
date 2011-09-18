#include <sanguis/server/level_calculate.hpp>
#include <sanguis/server/space_unit.hpp>
#include <fcppt/config/external_begin.hpp>
#include <cmath>
#include <fcppt/config/external_end.hpp>

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
