#include <sanguis/creator/count.hpp>
#include <sanguis/creator/exception.hpp>
#include <sanguis/creator/grid.hpp>
#include <sanguis/creator/opening_container.hpp>
#include <sanguis/creator/pos.hpp>
#include <sanguis/creator/size_type.hpp>
#include <sanguis/creator/spawn_container.hpp>
#include <sanguis/creator/spawn_pos.hpp>
#include <sanguis/creator/spawn_type.hpp>
#include <sanguis/creator/tile.hpp>
#include <sanguis/creator/tile_is_visible.hpp>
#include <sanguis/creator/aux_/closest_empty.hpp>
#include <sanguis/creator/aux_/enemy_type_container.hpp>
#include <sanguis/creator/aux_/log.hpp>
#include <sanguis/creator/aux_/optional_pos.hpp>
#include <sanguis/creator/aux_/place_spawners.hpp>
#include <sanguis/creator/aux_/random/generator.hpp>
#include <sanguis/creator/aux_/random/uniform_int_wrapper_impl.hpp>
#include <sanguis/creator/aux_/random/uniform_pos.hpp>
#include <fcppt/text.hpp>
#include <fcppt/assert/pre.hpp>
#include <fcppt/assert/error_message.hpp>
#include <fcppt/log/_.hpp>
#include <fcppt/log/error.hpp>
#include <fcppt/random/distribution/make_basic.hpp>
#include <fcppt/random/distribution/parameters/make_uniform_indices_advanced.hpp>


sanguis::creator::spawn_container
sanguis::creator::aux_::place_spawners(
	sanguis::creator::grid &_grid,
	sanguis::creator::opening_container const &_openings,
	sanguis::creator::count const _spawner_count,
	sanguis::creator::aux_::random::generator &_generator,
	sanguis::creator::aux_::enemy_type_container const &_enemy_types
)
{
	sanguis::creator::aux_::random::uniform_pos
	random_pos{
		_generator,
		_grid.size()
	};

	auto random_monster(
		fcppt::random::distribution::make_basic(
			fcppt::random::distribution::parameters::make_uniform_indices_advanced<
				sanguis::creator::aux_::random::uniform_int_wrapper
			>(
				_enemy_types
			)
		)
	);

	sanguis::creator::spawn_container
	spawners;

	sanguis::creator::spawn_container::size_type
	current_spawners{
		0u
	};

	sanguis::creator::count iterations{
		0u
	};

	while(
		current_spawners
		<
		_spawner_count
	)
	{
		sanguis::creator::aux_::optional_pos const
		candidate{
			sanguis::creator::aux_::closest_empty(
				_grid,
				random_pos()
			)
		};

		FCPPT_ASSERT_ERROR_MESSAGE(
			candidate.has_value(),
			FCPPT_TEXT(
				"Could not find a free tile anywhere!"
			)
		);


		if(
			!_openings.empty()
			&&
			!
			sanguis::creator::tile_is_visible(
				_grid,
				*candidate,
				_openings[0].get()
			)
		)
		{
			_grid
			[
				*candidate
			] =
				sanguis::creator::tile::spawner;

			spawners.push_back(
				sanguis::creator::spawn{
					sanguis::creator::spawn_pos{
						*candidate
					},
					_enemy_types[
						random_monster(
							_generator
						)
					],
					sanguis::creator::spawn_type::spawner
				}
			);

			++current_spawners;
		}

		if(
			++iterations
			>
			_spawner_count * 5
		)
		{
			FCPPT_LOG_ERROR(
				sanguis::creator::aux_::log(),
				fcppt::log::_
					<< FCPPT_TEXT("gave up on placing ")
					<< (_spawner_count - current_spawners)
					<< FCPPT_TEXT(" spawners due to visibility after ")
					<< iterations
					<< FCPPT_TEXT(" tries.")
			);

			break;
		}
	}

	return
		spawners;
}


