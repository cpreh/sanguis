#include <sanguis/duration_second.hpp>
#include <sanguis/server/exp.hpp>
#include <sanguis/server/health.hpp>
#include <sanguis/server/pickup_probability.hpp>
#include <sanguis/server/ai/create_simple.hpp>
#include <sanguis/server/ai/sight_range.hpp>
#include <sanguis/server/damage/no_armor.hpp>
#include <sanguis/server/entities/movement_speed.hpp>
#include <sanguis/server/entities/unique_ptr.hpp>
#include <sanguis/server/entities/enemies/enemy.hpp>
#include <sanguis/server/entities/enemies/factory/ghost.hpp>
#include <sanguis/server/entities/enemies/factory/parameters.hpp>
#include <sanguis/server/weapons/base_cooldown.hpp>
#include <sanguis/server/weapons/damage.hpp>
#include <sanguis/server/weapons/melee.hpp>
#include <sanguis/server/weapons/range.hpp>
#include <fcppt/make_unique_ptr.hpp>

#include <sanguis/server/radius.hpp>
#include <sanguis/server/auras/buff.hpp>
#include <sanguis/server/auras/influence.hpp>
#include <sanguis/server/buffs/slow.hpp>
#include <sanguis/server/entities/enemies/unique_ptr.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>

sanguis::server::entities::unique_ptr
sanguis::server::entities::enemies::factory::ghost(
	sanguis::server::entities::enemies::factory::parameters const &_parameters
)
{
	sanguis::server::entities::enemies::unique_ptr ret(
		fcppt::make_unique_ptr<
			sanguis::server::entities::enemies::enemy
		>(
			_parameters.diff_clock(),
			_parameters.enemy_type(),
			_parameters.load_context(),
			sanguis::server::damage::no_armor(),
			sanguis::server::health(
				2.f
				*
				_parameters.difficulty().get()
			),
			sanguis::server::entities::movement_speed(
				60.f
			),
			sanguis::server::ai::create_simple(
				sanguis::server::ai::sight_range(
					1000.f
				)
			),
			fcppt::make_unique_ptr<
				sanguis::server::weapons::melee
			>(
				_parameters.diff_clock(),
				sanguis::server::weapons::range(
					75.f
				),
				sanguis::server::weapons::base_cooldown(
					sanguis::duration_second(
						2.f
					)
				),
				sanguis::server::weapons::damage(
					5.f
				)
			),
			sanguis::server::pickup_probability(
				1.f//0.1f
			),
			sanguis::server::exp(
				10.f
			),
			_parameters.difficulty(),
			_parameters.spawn_owner()
		)
	);

	ret->add_aura(
		fcppt::make_unique_ptr<
			sanguis::server::auras::buff
		>(
			sanguis::server::radius(
				200.f
			),
			ret->team(),
			sanguis::server::auras::influence::debuff,
			[]()
			{
				return
					fcppt::make_unique_ptr<
						sanguis::server::buffs::slow
					>(
						sanguis::server::buffs::slow::factor(
							0.9f
						)
					);
			}
		)
	);

	return
		std::move(
			ret
		);
}
