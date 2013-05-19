#include <sanguis/creator/opening_container.hpp>
#include <sanguis/creator/parameters.hpp>
#include <sanguis/creator/randgen.hpp>
#include <sanguis/creator/size.hpp>


sanguis::creator::parameters::parameters(
	sanguis::creator::randgen &_randgen,
	sanguis::creator::size const &_size,
	sanguis::creator::opening_container const &_openings
)
:
	randgen_(
		_randgen
	),
	size_(
		_size
	),
	openings_(
		_openings
	)
{
}

sanguis::creator::randgen &
sanguis::creator::parameters::randgen() const
{
	return randgen_;
}

sanguis::creator::size const &
sanguis::creator::parameters::size() const
{
	return size_;
}

sanguis::creator::opening_container const &
sanguis::creator::parameters::openings() const
{
	return openings_;
}
