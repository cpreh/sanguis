#include <sanguis/creator/enemy_kind.hpp>
#include <sanguis/creator/exception.hpp>
#include <sanguis/creator/generate.hpp>
#include <sanguis/creator/opening_count.hpp>
#include <sanguis/creator/spawn.hpp>
#include <sanguis/creator/top_parameters.hpp>
#include <sanguis/creator/top_result.hpp>
#include <sanguis/creator/impl/generator_map.hpp>
#include <sanguis/creator/impl/parameters.hpp>
#include <sanguis/creator/impl/result.hpp>
#include <sanguis/creator/impl/random/generator.hpp>
#include <fcppt/make_enum_range.hpp>
#include <fcppt/text.hpp>
#include <fcppt/algorithm/contains_if.hpp>
#include <fcppt/assert/error.hpp>
#include <fcppt/container/find_exn.hpp>
#include <fcppt/math/dim/comparison.hpp>


sanguis::creator::top_result
sanguis::creator::generate(
	sanguis::creator::top_parameters const &_parameters
)
{
	sanguis::creator::impl::random::generator gen(
		_parameters.seed()
	);

	sanguis::creator::impl::result const result(
		fcppt::container::find_exn(
			sanguis::creator::impl::generator_map(),
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
			sanguis::creator::impl::parameters(
				gen,
				_parameters.spawn_boss(),
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

	if(
		_parameters.spawn_boss().get()
	)
		FCPPT_ASSERT_ERROR(
			fcppt::algorithm::contains_if(
				result.spawns(),
				[](
					sanguis::creator::spawn const &_spawn
				)
				{
					return
						_spawn.enemy_kind()
						==
						sanguis::creator::enemy_kind::boss;
				}
			)
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
