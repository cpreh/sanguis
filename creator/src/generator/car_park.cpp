#include <sanguis/creator/generator/car_park.hpp>
#include <sanguis/creator/generator/parameters.hpp>
#include <sanguis/creator/generator/result.hpp>

sanguis::creator::generator::result const
sanguis::creator::generator::car_park(
	generator::parameters const &
)
{
	return
		generator::result(
			geometry::shape_container()
		); // FIXME:
}
