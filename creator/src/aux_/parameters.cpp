#include <sanguis/creator/opening_container.hpp>
#include <sanguis/creator/aux_/parameters.hpp>
#include <sanguis/creator/aux_/randgen.hpp>


sanguis::creator::aux_::parameters::parameters(
	sanguis::creator::aux_::randgen &_randgen,
	sanguis::creator::opening_count const _opening_count
)
:
	randgen_(
		_randgen
	),
	opening_count_(
		_opening_count
	)
{
}

sanguis::creator::aux_::randgen &
sanguis::creator::aux_::parameters::randgen() const
{
	return randgen_;
}

sanguis::creator::opening_count const
sanguis::creator::aux_::parameters::opening_count() const
{
	return opening_count_;
}
