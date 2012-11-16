#include <sanguis/creator/generator/car_park.hpp>
#include <sanguis/creator/generator/name.hpp>
#include <sanguis/creator/generator/parameters.hpp>
#include <sanguis/creator/generator/result.hpp>
#include <sanguis/creator/generator/seed.hpp>
#include <sanguis/creator/generator/size.hpp>
#include <fcppt/math/dim/object_impl.hpp>
#include <fcppt/text.hpp>

#include <sanguis/creator/generator/randgen.hpp>
#include <sanguis/creator/geometry/depth.hpp>
#include <sanguis/creator/geometry/polygon.hpp>
#include <sanguis/creator/geometry/shape.hpp>
#include <sanguis/creator/geometry/shape_container.hpp>
#include <sanguis/creator/geometry/solidity.hpp>
#include <sanguis/creator/geometry/texture_name.hpp>
#include <sanguis/creator/geometry/texture_point.hpp>
#include <sanguis/creator/geometry/unit.hpp>
#include <sanguis/creator/geometry/vector.hpp>
#include <sanguis/creator/geometry/vertex.hpp>
#include <fcppt/assign/make_container.hpp>
#include <fcppt/random/distribution/uniform_int.hpp>


sanguis::creator::generator::result const
sanguis::creator::generator::car_park(
	sanguis::creator::generator::parameters const &_parameters
)
{
	typedef fcppt::random::distribution::uniform_int<
		sanguis::creator::geometry::unit
	> uniform_unit;

	uniform_unit test_distribution(
		uniform_unit::min(
			0
		),
		uniform_unit::max(
			1000
		)
	);

	sanguis::creator::geometry::unit const rand_value(
		test_distribution(
			_parameters.randgen()
		)
	);

	// FIXME:
	return
		sanguis::creator::generator::result(
			fcppt::assign::make_container<
				sanguis::creator::geometry::shape_container
			>(
				sanguis::creator::geometry::shape(
					fcppt::assign::make_container<
						sanguis::creator::geometry::polygon
					>(
						sanguis::creator::geometry::vertex(
							sanguis::creator::geometry::vector(
								0,
								0
							),
							sanguis::creator::geometry::texture_point(
								0,
								0
							)
						)
					)
					(
						sanguis::creator::geometry::vertex(
							sanguis::creator::geometry::vector(
								0,
								1000
							),
							sanguis::creator::geometry::texture_point(
								0,
								0.5f
							)
						)
					)
					(
						sanguis::creator::geometry::vertex(
							sanguis::creator::geometry::vector(
								2000,
								2000
							),
							sanguis::creator::geometry::texture_point(
								1,
								1
							)
						)
					)
					(
						sanguis::creator::geometry::vertex(
							sanguis::creator::geometry::vector(
								1000,
								500
							),
							sanguis::creator::geometry::texture_point(
								0.5f,
								0.25f
							)
						)
					)
					,
					sanguis::creator::geometry::solidity::solid,
					sanguis::creator::geometry::depth(
						0
					),
					sanguis::creator::geometry::texture_name(
						FCPPT_TEXT("asphalt")
					)
				)
			),
			sanguis::creator::generator::seed(
				0u
			),
			sanguis::creator::generator::name(
				FCPPT_TEXT("car_park")
			),
			sanguis::creator::generator::size(
				3000,
				3000
			)
		);
}
