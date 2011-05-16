#include <sanguis/creator/generator/car_park.hpp>
#include <sanguis/creator/generator/name.hpp>
#include <sanguis/creator/generator/parameters.hpp>
#include <sanguis/creator/generator/result.hpp>
#include <sanguis/creator/generator/seed.hpp>
#include <sanguis/creator/generator/size.hpp>
#include <fcppt/math/dim/basic_impl.hpp>
#include <fcppt/text.hpp>

sanguis::creator::generator::result const
sanguis::creator::generator::car_park(
	generator::parameters const &
)
{
	return
		generator::result(
			geometry::shape_container(),
			generator::seed(0),
			generator::name(
				FCPPT_TEXT("car_park")
			),
			generator::size::null()
		); // FIXME:
}
