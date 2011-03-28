#include <sanguis/creator/generator/parameters.hpp>

sanguis::creator::generator::parameters::parameters(
	generator::randgen &_randgen,
	geometry::rect const &_area,
	generator::opening_container const &_openings
)
:
	randgen_(_randgen),
	area_(_area),
	openings_(_openings)
{
}

sanguis::creator::generator::randgen &
sanguis::creator::generator::parameters::randgen() const
{
	return randgen_;
}

sanguis::creator::geometry::rect const &
sanguis::creator::generator::parameters::area() const
{
	return area_;
}

sanguis::creator::generator::opening_container const &
sanguis::creator::generator::parameters::openings() const
{
	return openings_;
}
