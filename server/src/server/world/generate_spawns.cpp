#include <sanguis/random_generator_fwd.hpp>
#include <sanguis/creator/spawn.hpp>
#include <sanguis/creator/spawn_type.hpp>
#include <sanguis/server/entities/base.hpp>
#include <sanguis/server/environment/load_context_fwd.hpp>
#include <sanguis/server/world/difficulty.hpp>
#include <sanguis/server/world/generate_spawns.hpp>
#include <sanguis/server/world/generate_single_spawns.hpp>
#include <sanguis/server/world/make_spawner.hpp>
#include <fcppt/assign/make_container.hpp>
#include <fcppt/assert/unreachable.hpp>


sanguis::server::world::insert_pair_container
sanguis::server::world::generate_spawns(
	sanguis::creator::spawn const &_spawn,
	sanguis::random_generator &_random_generator,
	sanguis::server::environment::load_context &_load_context,
	sanguis::server::world::difficulty const _difficulty
)
{
	switch(
		_spawn.spawn_type()
	)
	{
	case sanguis::creator::spawn_type::single:
		return
			sanguis::server::world::generate_single_spawns(
				_spawn.enemy_type(),
				_spawn.enemy_kind(),
				_spawn.pos(),
				_random_generator,
				_load_context,
				_difficulty
			);
	case sanguis::creator::spawn_type::spawner:
		return
			fcppt::assign::make_container<
				sanguis::server::world::insert_pair_container
			>(
				sanguis::server::world::make_spawner(
					_spawn.enemy_type(),
					_spawn.enemy_kind(),
					_spawn.pos(),
					_random_generator,
					_difficulty
				)
			).move_container();
	}

	FCPPT_ASSERT_UNREACHABLE;
}
