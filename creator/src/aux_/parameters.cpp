#include <sanguis/creator/opening_count_array.hpp>
#include <sanguis/creator/spawn_boss.hpp>
#include <sanguis/creator/aux_/parameters.hpp>
#include <sanguis/creator/aux_/random/generator_fwd.hpp>


sanguis::creator::aux_::parameters::parameters(
	sanguis::creator::aux_::random::generator &_randgen,
	sanguis::creator::spawn_boss const _spawn_boss,
	sanguis::creator::opening_count_array const _opening_count_array
)
:
	randgen_(
		_randgen
	),
	spawn_boss_{
		_spawn_boss
	},
	opening_count_array_(
		_opening_count_array
	)
{
}

sanguis::creator::aux_::random::generator &
sanguis::creator::aux_::parameters::randgen() const
{
	return
		randgen_;
}

sanguis::creator::spawn_boss const
sanguis::creator::aux_::parameters::spawn_boss() const
{
	return
		spawn_boss_;
}

sanguis::creator::opening_count_array const
sanguis::creator::aux_::parameters::opening_count_array() const
{
	return
		opening_count_array_;
}
