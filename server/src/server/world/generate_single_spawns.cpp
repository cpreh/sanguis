#include <sanguis/random_generator_fwd.hpp>
#include <sanguis/creator/spawn_pos.hpp>
#include <sanguis/creator/spawn_type.hpp>
#include <sanguis/load/enemy_name.hpp>
#include <sanguis/server/model_name.hpp>
#include <sanguis/server/model_size.hpp>
#include <sanguis/server/entities/auto_weak_link.hpp>
#include <sanguis/server/entities/base.hpp>
#include <sanguis/server/entities/spawn_owner.hpp>
#include <sanguis/server/entities/enemies/create.hpp>
#include <sanguis/server/entities/enemies/special_chance.hpp>
#include <sanguis/server/environment/load_context.hpp>
#include <sanguis/server/world/difficulty.hpp>
#include <sanguis/server/world/generate_single_spawns.hpp>
#include <sanguis/server/world/insert_pair_container.hpp>
#include <sanguis/server/world/place_callback.hpp>
#include <sanguis/server/world/place_multiple.hpp>


sanguis::server::world::insert_pair_container
sanguis::server::world::generate_single_spawns(
	sanguis::creator::enemy_type const _type,
	sanguis::creator::spawn_pos const _pos,
	sanguis::random_generator &_random_generator,
	sanguis::server::environment::load_context &_load_context,
	sanguis::server::world::difficulty const _difficulty
)
{
	return
		sanguis::server::world::place_multiple(
			_random_generator,
			sanguis::server::world::place_callback(
				[
					&_random_generator,
					_type,
					_difficulty,
					&_load_context]
				{
					return
						sanguis::server::entities::enemies::create(
							_random_generator,
							_type,
							_difficulty,
							_load_context,
							sanguis::server::entities::spawn_owner(
								sanguis::server::entities::auto_weak_link()
							),
							sanguis::server::entities::enemies::special_chance(
								0.05f
							)
						);
				}
			),
			_pos.get(),
			_load_context.model_size(
				sanguis::server::model_name(
					sanguis::load::enemy_name(
						_type
					)
				)
			)
		);
}
