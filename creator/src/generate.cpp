#include <sanguis/creator/exception.hpp>
#include <sanguis/creator/generate.hpp>
#include <sanguis/creator/top_parameters.hpp>
#include <sanguis/creator/top_result.hpp>
#include <sanguis/creator/aux/parameters.hpp>
#include <sanguis/creator/aux/randgen.hpp>
#include <sanguis/creator/aux/result.hpp>
#include <sanguis/creator/aux/generators/maze.hpp>
#include <sanguis/creator/aux/generators/lines.hpp>
#include <fcppt/text.hpp>
#include <fcppt/assert/error.hpp>
#include <fcppt/config/external_begin.hpp>
#include <map>
#include <utility>
#include <fcppt/config/external_end.hpp>


namespace
{

typedef
sanguis::creator::aux::result
(*generator_function)(
	sanguis::creator::aux::parameters const &
);

typedef std::map<
	sanguis::creator::name,
	generator_function
> generator_map;

generator_map const generators{
	std::make_pair(
		sanguis::creator::name(
			FCPPT_TEXT("maze")
		),
		&sanguis::creator::aux::generators::maze
	),
	std::make_pair(
		sanguis::creator::name(
			FCPPT_TEXT("lines")
		),
		&sanguis::creator::aux::generators::lines
	)
};

}

sanguis::creator::top_result
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

	sanguis::creator::aux::randgen gen(
		_parameters.seed()
	);

	sanguis::creator::aux::result const result(
		it->second(
			sanguis::creator::aux::parameters(
				gen,
				_parameters.opening_count()
			)
		)
	);

	FCPPT_ASSERT_ERROR(
		result.openings().size()
		==
		_parameters.opening_count().get()
	);

	return
		sanguis::creator::top_result(
			_parameters.seed(),
			_parameters.name(),
			result.grid(),
			result.openings()
		);
}
