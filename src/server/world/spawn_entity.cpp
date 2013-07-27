#include <sanguis/diff_clock_fwd.hpp>
#include <sanguis/enemy_type.hpp>
#include <sanguis/random_generator_fwd.hpp>
#include <sanguis/creator/spawn_fwd.hpp>
#include <sanguis/server/entities/auto_weak_link.hpp>
#include <sanguis/server/entities/base.hpp>
#include <sanguis/server/entities/unique_ptr.hpp>
#include <sanguis/server/entities/enemies/create.hpp>
#include <sanguis/server/entities/enemies/spawn_owner.hpp>
#include <sanguis/server/environment/load_context_fwd.hpp>
#include <sanguis/server/world/spawn_entity.hpp>


sanguis::server::entities::unique_ptr
sanguis::server::world::spawn_entity(
	sanguis::creator::spawn const &_spawn,
	sanguis::diff_clock const &_diff_clock,
	sanguis::random_generator &_random_generator,
	sanguis::server::environment::load_context &_load_context
)
{
	return
		sanguis::server::entities::enemies::create(
			_diff_clock,
			_random_generator,
			sanguis::enemy_type::maggot, // TODO!
			_load_context,
			sanguis::server::entities::enemies::spawn_owner(
				sanguis::server::entities::auto_weak_link()
			)
		);
}
