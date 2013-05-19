#include <sanguis/creator/car_park.hpp>
#include <sanguis/creator/exception.hpp>
#include <sanguis/creator/generate.hpp>
#include <sanguis/creator/opening_container.hpp>
#include <sanguis/creator/parameters.hpp>
#include <sanguis/creator/randgen.hpp>
#include <sanguis/creator/result.hpp>
#include <sanguis/creator/top_parameters.hpp>
#include <fcppt/text.hpp>
#include <fcppt/assign/make_container.hpp>
#include <fcppt/config/external_begin.hpp>
#include <map>
#include <utility>
#include <fcppt/config/external_end.hpp>


namespace
{

typedef
sanguis::creator::result
(*generator_function)(
	sanguis::creator::parameters const &
);

typedef std::map<
	sanguis::creator::name,
	generator_function
> generator_map;

generator_map const generators(
	fcppt::assign::make_container<
		generator_map
	>(
		std::make_pair(
			sanguis::creator::name(
				FCPPT_TEXT("car_park")
			),
			&sanguis::creator::car_park
		)
	)
);

}

sanguis::creator::result const
sanguis::creator::generate(
	sanguis::creator::top_parameters const &_parameters
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

	sanguis::creator::randgen gen(
		_parameters.seed()
	);

	return
		it->second(
			sanguis::creator::parameters(
				gen,
				_parameters.size(),
				sanguis::creator::opening_container()
			)
		);
}
