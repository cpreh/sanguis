#include <sanguis/random_generator_fwd.hpp>
#include <sanguis/creator/spawn_pos.hpp>
#include <sanguis/creator/spawn_type.hpp>
#include <sanguis/server/entities/auto_weak_link.hpp>
#include <sanguis/server/entities/base.hpp>
#include <sanguis/server/entities/insert_parameters_center.hpp>
#include <sanguis/server/entities/spawn_owner.hpp>
#include <sanguis/server/entities/enemies/create.hpp>
#include <sanguis/server/entities/enemies/special_chance.hpp>
#include <sanguis/server/environment/load_context_fwd.hpp>
#include <sanguis/server/world/difficulty.hpp>
#include <sanguis/server/world/generate_single_spawns.hpp>
#include <sanguis/server/world/grid_pos_to_center.hpp>
#include <sanguis/server/world/insert_pair.hpp>
#include <sanguis/server/world/insert_pair_container.hpp>
#include <fcppt/assign/make_container.hpp>


sanguis::server::world::insert_pair_container
sanguis::server::world::generate_single_spawns(
	sanguis::creator::enemy_type const _type,
	sanguis::creator::spawn_pos const _pos,
	sanguis::random_generator &_random_generator,
	sanguis::server::environment::load_context &_load_context,
	sanguis::server::world::difficulty const _difficulty
)
{
	// TODO
	return
		fcppt::assign::make_container<
			sanguis::server::world::insert_pair_container
		>(
			sanguis::server::world::insert_pair(
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
				),
				sanguis::server::entities::insert_parameters_center(
					sanguis::server::world::grid_pos_to_center(
						_pos.get()
					)
				)
			)
		).move_container();
}
