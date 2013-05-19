#include <sanguis/creator/car_park.hpp>
#include <sanguis/creator/grid.hpp>
#include <sanguis/creator/name.hpp>
#include <sanguis/creator/parameters.hpp>
#include <sanguis/creator/result.hpp>
#include <sanguis/creator/seed.hpp>
#include <sanguis/creator/tile.hpp>
#include <fcppt/text.hpp>

/*
#include <sanguis/creator/randgen.hpp>
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
#include <fcppt/random/distribution/basic.hpp>
#include <fcppt/random/distribution/parameters/uniform_int.hpp>
*/


sanguis::creator::result
sanguis::creator::car_park(
	sanguis::creator::parameters const &_parameters
)
{
	return
		sanguis::creator::result(
			sanguis::creator::grid(
				sanguis::creator::grid::dim(
					64,
					64
				),
				sanguis::creator::tile::nothing
			),
			sanguis::creator::seed(
				0u
			),
			sanguis::creator::name(
				FCPPT_TEXT("car_park")
			)
		);
/*
	typedef fcppt::random::distribution::basic<
		fcppt::random::distribution::parameters::uniform_int<
			sanguis::creator::geometry::unit
		>
	> uniform_unit;

	uniform_unit x_distribution(
		uniform_unit::param_type::min(
			0
		),
		uniform_unit::param_type::max(
			_parameters.area().w()
		)
	);

	uniform_unit y_distribution(
		uniform_unit::param_type::min(
			0
		),
		uniform_unit::param_type::max(
			_parameters.area().h()
		)
	);

	sanguis::creator::geometry::shape_container cars;

	sanguis::creator::geometry::unit const half_car_width(
		64);
	sanguis::creator::geometry::unit const half_car_height(
		32);

	for (unsigned i = 0; i < 400; ++i)
	{
		sanguis::creator::geometry::unit const x(
			x_distribution(
				_parameters.randgen()
			)
		);

		sanguis::creator::geometry::unit const y(
			y_distribution(
				_parameters.randgen()
			)
		);

		cars.push_back(
			sanguis::creator::geometry::shape(
				fcppt::assign::make_container<
					sanguis::creator::geometry::polygon
				>(
					sanguis::creator::geometry::vertex(
						sanguis::creator::geometry::vector(
							x - half_car_width,
							y - half_car_height
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
							x - half_car_width,
							y + half_car_height
						),
						sanguis::creator::geometry::texture_point(
							0,
							1
						)
					)
				)
				(
					sanguis::creator::geometry::vertex(
						sanguis::creator::geometry::vector(
							x + half_car_width,
							y + half_car_height
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
							x + half_car_width,
							y - half_car_height
						),
						sanguis::creator::geometry::texture_point(
							1,
							0
						)
					)
				)
				,
				sanguis::creator::geometry::solidity::solid,
				sanguis::creator::geometry::depth(
					0
				),
				sanguis::creator::geometry::texture_name(
					FCPPT_TEXT("car")
				)
			)
		);
	}

	return
		sanguis::creator::result(
			cars,
			sanguis::creator::seed(
				0u
			),
			sanguis::creator::name(
				FCPPT_TEXT("car_park")
			),
			sanguis::creator::size(
				3000,
				3000
			)
		);*/
}
