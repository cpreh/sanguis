#include <sanguis/diff_clock_fwd.hpp>
#include <sanguis/random_generator_fwd.hpp>
#include <sanguis/creator/spawn.hpp>
#include <sanguis/creator/spawn_type.hpp>
#include <sanguis/server/entities/auto_weak_link.hpp>
#include <sanguis/server/entities/base.hpp>
#include <sanguis/server/entities/spawn_owner.hpp>
#include <sanguis/server/entities/unique_ptr.hpp>
#include <sanguis/server/entities/enemies/create.hpp>
#include <sanguis/server/environment/load_context_fwd.hpp>
#include <sanguis/server/world/difficulty.hpp>
#include <sanguis/server/world/make_spawner.hpp>
#include <sanguis/server/world/spawn_entity.hpp>
#include <fcppt/assert/unreachable.hpp>


sanguis::server::entities::unique_ptr
sanguis::server::world::spawn_entity(
	sanguis::creator::spawn const &_spawn,
	sanguis::diff_clock const &_diff_clock,
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
			sanguis::server::entities::enemies::create(
				_diff_clock,
				_random_generator,
				_spawn.enemy_type(),
				_difficulty,
				_load_context,
				sanguis::server::entities::spawn_owner(
					sanguis::server::entities::auto_weak_link()
				)
			);
	case sanguis::creator::spawn_type::spawner:
		return
			sanguis::server::world::make_spawner(
				_spawn.enemy_type(),
				_diff_clock,
				_random_generator,
				_difficulty
			);
	}

	FCPPT_ASSERT_UNREACHABLE;
}
