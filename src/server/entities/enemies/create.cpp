#include <sanguis/diff_clock_fwd.hpp>
#include <sanguis/random_generator_fwd.hpp>
#include <sanguis/creator/enemy_type.hpp>
#include <sanguis/server/entities/base.hpp>
#include <sanguis/server/entities/enemies/base_difficulty.hpp>
#include <sanguis/server/entities/enemies/create.hpp>
#include <sanguis/server/entities/enemies/difficulty.hpp>
#include <sanguis/server/entities/enemies/difficulty_value.hpp>
#include <sanguis/server/entities/enemies/spawn_owner_fwd.hpp>
#include <sanguis/server/entities/enemies/factory/ghost.hpp>
#include <sanguis/server/entities/enemies/factory/maggot.hpp>
#include <sanguis/server/entities/enemies/factory/skeleton.hpp>
#include <sanguis/server/entities/enemies/factory/spider.hpp>
#include <sanguis/server/entities/enemies/factory/wolf.hpp>
#include <sanguis/server/entities/enemies/factory/zombie00.hpp>
#include <sanguis/server/entities/enemies/factory/zombie01.hpp>
#include <sanguis/server/entities/enemies/factory/parameters.hpp>
#include <sanguis/server/environment/load_context_fwd.hpp>
#include <sanguis/server/world/difficulty.hpp>
#include <fcppt/assert/unreachable.hpp>
#include <fcppt/cast/int_to_float.hpp>


sanguis::server::entities::unique_ptr
sanguis::server::entities::enemies::create(
	sanguis::diff_clock const &_diff_clock,
	sanguis::random_generator &_random_generator,
	sanguis::creator::enemy_type const _enemy_type,
	sanguis::server::world::difficulty const _difficulty,
	sanguis::server::environment::load_context &_load_context,
	sanguis::server::entities::enemies::spawn_owner const &_spawn
)
{
	sanguis::server::entities::enemies::factory::parameters const parameters(
		_diff_clock,
		_random_generator,
		_enemy_type,
		sanguis::server::entities::enemies::difficulty(
			sanguis::server::entities::enemies::base_difficulty(
				_enemy_type
			)
			*
			fcppt::cast::int_to_float<
				sanguis::server::entities::enemies::difficulty_value
			>(
				_difficulty.get()
			)
		),
		_load_context,
		_spawn
	);

	switch(
		_enemy_type
	)
	{
	case sanguis::creator::enemy_type::zombie00:
		return
			sanguis::server::entities::enemies::factory::zombie00(
				parameters
			);
	case sanguis::creator::enemy_type::zombie01:
		return
			sanguis::server::entities::enemies::factory::zombie01(
				parameters
			);
	case sanguis::creator::enemy_type::wolf_black:
	case sanguis::creator::enemy_type::wolf_brown:
	case sanguis::creator::enemy_type::wolf_white:
		return
			sanguis::server::entities::enemies::factory::wolf(
				parameters
			);
	case sanguis::creator::enemy_type::skeleton:
		return
			sanguis::server::entities::enemies::factory::skeleton(
				parameters
			);
	case sanguis::creator::enemy_type::maggot:
		return
			sanguis::server::entities::enemies::factory::maggot(
				parameters
			);
	case sanguis::creator::enemy_type::ghost:
		return
			sanguis::server::entities::enemies::factory::ghost(
				parameters
			);
	case sanguis::creator::enemy_type::spider:
		return
			sanguis::server::entities::enemies::factory::spider(
				parameters
			);
	}

	FCPPT_ASSERT_UNREACHABLE;
}
