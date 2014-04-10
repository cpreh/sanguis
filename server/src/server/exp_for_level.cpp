#include <sanguis/server/exp.hpp>
#include <sanguis/server/exp_for_level.hpp>
#include <sanguis/server/level.hpp>
#include <fcppt/literal.hpp>
#include <fcppt/cast/int_to_float.hpp>


sanguis::server::exp const
sanguis::server::exp_for_level(
	sanguis::server::level const _level
)
{
	// This function reverses level_from_exp
	return
		sanguis::server::exp(
			fcppt::cast::int_to_float<
				sanguis::server::exp::value_type
			>(
				_level.get()
				*
				_level.get()
			)
			/
			fcppt::literal<
				sanguis::server::exp::value_type
			>(
				0.09
			)
		);
}
