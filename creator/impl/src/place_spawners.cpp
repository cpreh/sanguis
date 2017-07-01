#include <sanguis/creator/count.hpp>
#include <sanguis/creator/enemy_kind.hpp>
#include <sanguis/creator/exception.hpp>
#include <sanguis/creator/grid.hpp>
#include <sanguis/creator/opening.hpp>
#include <sanguis/creator/opening_container_array.hpp>
#include <sanguis/creator/pos.hpp>
#include <sanguis/creator/size_type.hpp>
#include <sanguis/creator/spawn_boss.hpp>
#include <sanguis/creator/spawn_container.hpp>
#include <sanguis/creator/spawn_pos.hpp>
#include <sanguis/creator/spawn_type.hpp>
#include <sanguis/creator/tile.hpp>
#include <sanguis/creator/tile_is_visible.hpp>
#include <sanguis/creator/impl/closest_empty.hpp>
#include <sanguis/creator/impl/enemy_type_container.hpp>
#include <sanguis/creator/impl/place_boss.hpp>
#include <sanguis/creator/impl/place_spawners.hpp>
#include <sanguis/creator/impl/random/generator.hpp>
#include <sanguis/creator/impl/random/uniform_int_wrapper_impl.hpp>
#include <sanguis/creator/impl/random/uniform_pos.hpp>
#include <fcppt/text.hpp>
#include <fcppt/algorithm/fold.hpp>
#include <fcppt/assert/error_message.hpp>
#include <fcppt/assert/optional_error.hpp>
#include <fcppt/assert/pre.hpp>
#include <fcppt/container/grid/at_optional.hpp>
#include <fcppt/log/_.hpp>
#include <fcppt/log/error.hpp>
#include <fcppt/log/object_fwd.hpp>
#include <fcppt/optional/to_exception.hpp>
#include <fcppt/random/wrapper/make_uniform_container_advanced.hpp>


sanguis::creator::spawn_container
sanguis::creator::impl::place_spawners(
	fcppt::log::object &_log,
	sanguis::creator::grid &_grid,
	sanguis::creator::opening_container_array const &_openings,
	sanguis::creator::count const _spawner_count,
	sanguis::creator::impl::random::generator &_generator,
	sanguis::creator::impl::enemy_type_container const &_enemy_types,
	sanguis::creator::spawn_boss const _spawn_boss,
	sanguis::creator::tile const _spawner_tile
)
{
	sanguis::creator::impl::random::uniform_pos
	random_pos{
		_generator,
		_grid.size()
	};

	auto random_monster(
		FCPPT_ASSERT_OPTIONAL_ERROR(
			fcppt::random::wrapper::make_uniform_container_advanced<
				sanguis::creator::impl::random::uniform_int_wrapper
			>(
				_enemy_types
			)
		)
	);

	sanguis::creator::spawn_container
	spawners;

	if(
		_spawn_boss.get()
	)
		spawners.push_back(
			sanguis::creator::impl::place_boss(
				_openings
			)
		);

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
		sanguis::creator::pos const candidate{
			fcppt::optional::to_exception(
				sanguis::creator::impl::closest_empty(
					_grid,
					random_pos()
				),
				[]{
					return
						sanguis::creator::exception{
							FCPPT_TEXT(
								"Could not find a free tile anywhere!"
							)
						};
				}
			)
		};

		if(
			// TODO: Use any_of for ranges
			!fcppt::algorithm::fold(
				_openings[
					sanguis::creator::opening_type::entry
				],
				false,
				[
					&_grid,
					&candidate
				](
					sanguis::creator::opening const _cur,
					bool const _value
				)
				{
					return
						_value
						||
						sanguis::creator::tile_is_visible(
							_grid,
							candidate,
							_cur.get()
						);
				}
			)
		)
		{
			FCPPT_ASSERT_OPTIONAL_ERROR(
				fcppt::container::grid::at_optional(
					_grid,
					candidate
				)
			).get() =
				_spawner_tile;

			spawners.push_back(
				sanguis::creator::spawn{
					sanguis::creator::spawn_pos{
						candidate
					},
					random_monster(
						_generator
					),
					sanguis::creator::spawn_type::spawner,
					sanguis::creator::enemy_kind::normal
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
				_log,
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


