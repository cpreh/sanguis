#include <sanguis/creator/opening_container.hpp>
#include <sanguis/creator/aux/parameters.hpp>
#include <sanguis/creator/aux/randgen.hpp>


sanguis::creator::aux::parameters::parameters(
	sanguis::creator::aux::randgen &_randgen,
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

sanguis::creator::aux::randgen &
sanguis::creator::aux::parameters::randgen() const
{
	return randgen_;
}

sanguis::creator::opening_count const
sanguis::creator::aux::parameters::opening_count() const
{
	return opening_count_;
}
