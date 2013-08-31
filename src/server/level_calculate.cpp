#include <sanguis/server/exp.hpp>
#include <sanguis/server/level.hpp>
#include <sanguis/server/level_calculate.hpp>
#include <sanguis/server/space_unit.hpp>
#include <fcppt/literal.hpp>
#include <fcppt/strong_typedef_construct_cast.hpp>
#include <fcppt/config/external_begin.hpp>
#include <cmath>
#include <fcppt/config/external_end.hpp>


sanguis::server::level const
sanguis::server::level_calculate(
	sanguis::server::exp const _exp,
	sanguis::server::level
)
{
	return
		fcppt::strong_typedef_construct_cast<
			sanguis::server::level
		>(
			fcppt::literal<
				sanguis::server::space_unit
			>(
				0.3
			)
			*
			std::sqrt(
				_exp.get()
			)
		);
}
