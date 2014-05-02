#include <sanguis/duration_second.hpp>
#include <sanguis/creator/enemy_type.hpp>
#include <sanguis/creator/spawn_pos.hpp>
#include <sanguis/server/entities/base.hpp>
#include <sanguis/server/entities/insert_parameters_center.hpp>
#include <sanguis/server/entities/spawns/count_per_wave.hpp>
#include <sanguis/server/entities/spawns/interval.hpp>
#include <sanguis/server/entities/spawns/limit.hpp>
#include <sanguis/server/entities/spawns/limited.hpp>
#include <sanguis/server/entities/spawns/total_count.hpp>
#include <sanguis/server/world/difficulty.hpp>
#include <sanguis/server/world/grid_pos_to_center.hpp>
#include <sanguis/server/world/insert_pair.hpp>
#include <sanguis/server/world/make_spawner.hpp>
#include <fcppt/make_unique_ptr.hpp>


sanguis::server::world::insert_pair
sanguis::server::world::make_spawner(
	sanguis::creator::enemy_type const _enemy_type,
	sanguis::creator::spawn_pos const _pos,
	sanguis::random_generator &_random_generator,
	sanguis::server::world::difficulty const _difficulty
)
{
	return
		sanguis::server::world::insert_pair(
			fcppt::make_unique_ptr<
				sanguis::server::entities::spawns::limited
			>(
				_random_generator,
				_enemy_type,
				_difficulty,
				// TODO!
				sanguis::server::entities::spawns::count_per_wave(
					1u
				),
				sanguis::server::entities::spawns::interval(
					sanguis::duration_second(
						1.f
					)
				),
				sanguis::server::entities::spawns::limit(
					1u
				),
				sanguis::server::entities::spawns::total_count(
					5u
				)
			),
			sanguis::server::entities::insert_parameters_center(
				sanguis::server::world::grid_pos_to_center(
					_pos.get()
				)
			)
		);
}
