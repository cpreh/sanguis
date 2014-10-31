#include <sanguis/creator/exception.hpp>
#include <sanguis/creator/generate.hpp>
#include <sanguis/creator/opening_count.hpp>
#include <sanguis/creator/top_parameters.hpp>
#include <sanguis/creator/top_result.hpp>
#include <sanguis/creator/aux_/generator_map.hpp>
#include <sanguis/creator/aux_/parameters.hpp>
#include <sanguis/creator/aux_/result.hpp>
#include <sanguis/creator/aux_/random/generator.hpp>
#include <fcppt/make_enum_range.hpp>
#include <fcppt/text.hpp>
#include <fcppt/assert/error.hpp>
#include <fcppt/container/find_exn.hpp>
#include <fcppt/math/dim/comparison.hpp>


sanguis::creator::top_result
sanguis::creator::generate(
	sanguis::creator::top_parameters const &_parameters
)
{
	sanguis::creator::aux_::random::generator gen(
		_parameters.seed()
	);

	sanguis::creator::aux_::result const result(
		fcppt::container::find_exn(
			sanguis::creator::aux_::generator_map(),
			_parameters.name(),
			[
				&_parameters
			]
			{
				return
					sanguis::creator::exception(
						FCPPT_TEXT("Generator ")
						+
						_parameters.name().get()
						+
						FCPPT_TEXT(" not found!")
					);
			}
		)(
			sanguis::creator::aux_::parameters(
				gen,
				_parameters.opening_count_array()
			)
		)
	);

	for(
		auto const opening_type
		:
		fcppt::make_enum_range<
			sanguis::creator::opening_type
		>()
	)
		FCPPT_ASSERT_ERROR(
			result.openings()[
				opening_type
			].size()
			==
			_parameters.opening_count_array()[
				opening_type
			].get()
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
			_parameters.spawn_boss(),
			result.grid(),
			result.background_grid(),
			result.openings(),
			result.spawns(),
			result.destructibles()
		);
}
