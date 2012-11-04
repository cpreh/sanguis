#include <sanguis/creator/generator/generate.hpp>
#include <sanguis/creator/generator/car_park.hpp>
#include <sanguis/creator/generator/opening_container.hpp>
#include <sanguis/creator/generator/parameters.hpp>
#include <sanguis/creator/generator/randgen.hpp>
#include <sanguis/creator/generator/result.hpp>
#include <sanguis/creator/generator/top_parameters.hpp>
#include <sanguis/creator/geometry/rect.hpp>
#include <sanguis/creator/exception.hpp>
#include <fcppt/text.hpp>
#include <fcppt/assign/make_container.hpp>
#include <fcppt/math/dim/structure_cast.hpp>
#include <fcppt/config/external_begin.hpp>
#include <map>
#include <utility>
#include <fcppt/config/external_end.hpp>


namespace
{

typedef sanguis::creator::generator::result const
(*generator_function)(
	sanguis::creator::generator::parameters const &
);

typedef std::map<
	sanguis::creator::generator::name,
	generator_function
> generator_map;

generator_map const generators(
	fcppt::assign::make_container<
		generator_map
	>(
		std::make_pair(
			sanguis::creator::generator::name(
				FCPPT_TEXT("car_park")
			),
			&sanguis::creator::generator::car_park
		)
	)
);

}

sanguis::creator::generator::result const
sanguis::creator::generator::generate(
	sanguis::creator::generator::top_parameters const &_parameters
)
{
	generator_map::const_iterator const it(
		generators.find(
			_parameters.name()
		)
	);

	if(
		it == generators.end()
	)
		throw sanguis::creator::exception(
			FCPPT_TEXT("Generator ")
			+ _parameters.name().get()
			+ FCPPT_TEXT(" not found!")
		);

	sanguis::creator::generator::randgen gen(
		_parameters.seed()
	);

	return
		it->second(
			sanguis::creator::generator::parameters(
				gen,
				sanguis::creator::geometry::rect(
					sanguis::creator::geometry::rect::vector::null(),
					fcppt::math::dim::structure_cast<
						sanguis::creator::geometry::rect::dim
					>(
						_parameters.size()
					)
				),
				sanguis::creator::generator::opening_container()
			)
		);
}
