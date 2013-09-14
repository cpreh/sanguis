#include <sanguis/creator/exception.hpp>
#include <sanguis/creator/generate.hpp>
#include <sanguis/creator/top_parameters.hpp>
#include <sanguis/creator/top_result.hpp>
#include <sanguis/creator/aux_/generator_map.hpp>
#include <sanguis/creator/aux_/generator_map_type.hpp>
#include <sanguis/creator/aux_/parameters.hpp>
#include <sanguis/creator/aux_/randgen.hpp>
#include <sanguis/creator/aux_/result.hpp>
#include <fcppt/text.hpp>
#include <fcppt/assert/error.hpp>
#include <fcppt/math/dim/comparison.hpp>


sanguis::creator::top_result
sanguis::creator::generate(
	sanguis::creator::top_parameters const &_parameters
)
{
	sanguis::creator::aux_::generator_map_type const &generators(
		sanguis::creator::aux_::generator_map()
	);

	sanguis::creator::aux_::generator_map_type::const_iterator const it(
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

	sanguis::creator::aux_::randgen gen(
		_parameters.seed()
	);

	sanguis::creator::aux_::result const result(
		it->second(
			sanguis::creator::aux_::parameters(
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

	FCPPT_ASSERT_ERROR(
		result.grid().size()
		==
		result.background_grid().size()
	);

	return
		sanguis::creator::top_result(
			_parameters.seed(),
			_parameters.name(),
			result.grid(),
			result.background_grid(),
			result.openings(),
			result.spawns()
		);
}
