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
#include <fcppt/random/distribution/basic.hpp>
#include <fcppt/random/distribution/parameters/uniform_int.hpp>


sanguis::creator::generator::result const
sanguis::creator::generator::car_park(
	sanguis::creator::generator::parameters const &_parameters
)
{
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
		sanguis::creator::generator::result(
			cars,
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
