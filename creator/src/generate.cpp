#include <sanguis/creator/exception.hpp>
#include <sanguis/creator/generate.hpp>
#include <sanguis/creator/top_parameters.hpp>
#include <sanguis/creator/top_result.hpp>
#include <sanguis/creator/aux/generator_map.hpp>
#include <sanguis/creator/aux/generator_map_type.hpp>
#include <sanguis/creator/aux/parameters.hpp>
#include <sanguis/creator/aux/randgen.hpp>
#include <sanguis/creator/aux/result.hpp>
#include <fcppt/text.hpp>
#include <fcppt/assert/error.hpp>


sanguis::creator::top_result
sanguis::creator::generate(
	sanguis::creator::top_parameters const &_parameters
)
{
	sanguis::creator::aux::generator_map_type const &generators(
		sanguis::creator::aux::generator_map()
	);

	sanguis::creator::aux::generator_map_type::const_iterator const it(
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
