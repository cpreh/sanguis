#include <sanguis/creator/generator/car_park.hpp>
#include <sanguis/creator/generator/name.hpp>
#include <sanguis/creator/generator/parameters.hpp>
#include <sanguis/creator/generator/result.hpp>
#include <sanguis/creator/generator/seed.hpp>
#include <sanguis/creator/generator/size.hpp>
#include <fcppt/math/dim/basic_impl.hpp>
#include <fcppt/text.hpp>

#include <sanguis/creator/geometry/depth.hpp>
#include <sanguis/creator/geometry/polygon.hpp>
#include <sanguis/creator/geometry/shape.hpp>
#include <sanguis/creator/geometry/shape_container.hpp>
#include <sanguis/creator/geometry/solidity.hpp>
#include <sanguis/creator/geometry/texture_name.hpp>
#include <sanguis/creator/geometry/texture_point.hpp>
#include <sanguis/creator/geometry/vector.hpp>
#include <sanguis/creator/geometry/vertex.hpp>
#include <fcppt/assign/make_container.hpp>

sanguis::creator::generator::result const
sanguis::creator::generator::car_park(
	generator::parameters const &
)
{
	// FIXME:
	return
		generator::result(
			fcppt::assign::make_container<
				geometry::shape_container
			>(
				geometry::shape(
					fcppt::assign::make_container<
						geometry::polygon
					>(
						geometry::vertex(
							geometry::vector(
								0,
								0
							),
							geometry::texture_point(
								0,
								0
							)
						)
					)
					(
						geometry::vertex(
							geometry::vector(
								100,
								100
							),
							geometry::texture_point(
								1,
								1
							)
						)
					)
					(
						geometry::vertex(
							geometry::vector(
								0,
								50
							),
							geometry::texture_point(
								0,
								0.5f
							)
						)
					),
					geometry::solidity::solid,
					geometry::depth(
						0
					),
					geometry::texture_name(
						FCPPT_TEXT("asphalt")
					)
				)
			),
			generator::seed(0),
			generator::name(
				FCPPT_TEXT("car_park")
			),
			generator::size(
				1024,
				1024
			)
		);
}
