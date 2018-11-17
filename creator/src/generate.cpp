#include <sanguis/log_location.hpp>
#include <sanguis/log_parameters.hpp>
#include <sanguis/creator/enemy_kind.hpp>
#include <sanguis/creator/exception.hpp>
#include <sanguis/creator/generate.hpp>
#include <sanguis/creator/opening_count.hpp>
#include <sanguis/creator/spawn.hpp>
#include <sanguis/creator/top_parameters.hpp>
#include <sanguis/creator/top_result.hpp>
#include <sanguis/creator/impl/generator_map.hpp>
#include <sanguis/creator/impl/log_name.hpp>
#include <sanguis/creator/impl/parameters.hpp>
#include <sanguis/creator/impl/result.hpp>
#include <sanguis/creator/impl/random/generator.hpp>
#include <fcppt/strong_typedef_output.hpp>
#include <fcppt/text.hpp>
#include <fcppt/algorithm/contains_if.hpp>
#include <fcppt/assert/error.hpp>
#include <fcppt/container/find_opt_mapped.hpp>
#include <fcppt/enum/make_range.hpp>
#include <fcppt/log/debug.hpp>
#include <fcppt/log/object.hpp>
#include <fcppt/log/out.hpp>
#include <fcppt/math/dim/comparison.hpp>
#include <fcppt/optional/to_exception.hpp>


sanguis::creator::top_result
sanguis::creator::generate(
	sanguis::creator::top_parameters const &_parameters
)
{
	fcppt::log::object log{
		_parameters.log_context(),
		sanguis::log_location(),
		sanguis::log_parameters(
			sanguis::creator::impl::log_name()
		)
	};

	FCPPT_LOG_DEBUG(
		log,
		fcppt::log::out
			<<
			FCPPT_TEXT("Generating world \"")
			<<
			_parameters.name()
			<<
			FCPPT_TEXT("\" with seed ")
			<<
			_parameters.seed()
	);


	sanguis::creator::impl::random::generator gen(
		_parameters.seed()
	);

	sanguis::creator::impl::result const result(
		fcppt::optional::to_exception(
			fcppt::container::find_opt_mapped(
				sanguis::creator::impl::generator_map(),
				_parameters.name()
			),
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
		).get()(
			sanguis::creator::impl::parameters(
				log,
				gen,
				_parameters.spawn_boss(),
				_parameters.opening_count_array()
			)
		)
	);

	for(
		auto const opening_type
		:
		fcppt::enum_::make_range<
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
