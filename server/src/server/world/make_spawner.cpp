#include <sanguis/duration_second.hpp>
#include <sanguis/creator/enemy_type.hpp>
#include <sanguis/server/entities/base.hpp>
#include <sanguis/server/entities/unique_ptr.hpp>
#include <sanguis/server/entities/spawns/count_per_wave.hpp>
#include <sanguis/server/entities/spawns/interval.hpp>
#include <sanguis/server/entities/spawns/limit.hpp>
#include <sanguis/server/entities/spawns/limited.hpp>
#include <sanguis/server/entities/spawns/total_count.hpp>
#include <sanguis/server/world/difficulty.hpp>
#include <sanguis/server/world/make_spawner.hpp>
#include <fcppt/make_unique_ptr.hpp>


sanguis::server::entities::unique_ptr
sanguis::server::world::make_spawner(
	sanguis::creator::enemy_type const _enemy_type,
	sanguis::random_generator &_random_generator,
	sanguis::server::world::difficulty const _difficulty
)
{
	return
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
		);
}
