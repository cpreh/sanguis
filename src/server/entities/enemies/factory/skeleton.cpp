#include <sanguis/aura_type.hpp>
#include <sanguis/duration_second.hpp>
#include <sanguis/server/exp.hpp>
#include <sanguis/server/health.hpp>
#include <sanguis/server/pickup_probability.hpp>
#include <sanguis/server/team.hpp>
#include <sanguis/server/ai/create_simple.hpp>
#include <sanguis/server/ai/sight_range.hpp>
#include <sanguis/server/auras/buff.hpp>
#include <sanguis/server/auras/container.hpp>
#include <sanguis/server/auras/influence.hpp>
#include <sanguis/server/buffs/burn.hpp>
#include <sanguis/server/buffs/burn_create.hpp>
#include <sanguis/server/buffs/burn_interval.hpp>
#include <sanguis/server/buffs/define_special.hpp>
#include <sanguis/server/damage/fire.hpp>
#include <sanguis/server/damage/list.hpp>
#include <sanguis/server/damage/no_armor.hpp>
#include <sanguis/server/damage/unit.hpp>
#include <sanguis/server/entities/movement_speed.hpp>
#include <sanguis/server/entities/unique_ptr.hpp>
#include <sanguis/server/entities/enemies/enemy.hpp>
#include <sanguis/server/entities/enemies/factory/parameters.hpp>
#include <sanguis/server/entities/enemies/factory/skeleton.hpp>
#include <sanguis/server/weapons/base_cooldown.hpp>
#include <sanguis/server/weapons/damage.hpp>
#include <sanguis/server/weapons/melee.hpp>
#include <sanguis/server/weapons/range.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/assign/make_container.hpp>


sanguis::server::entities::unique_ptr
sanguis::server::entities::enemies::factory::skeleton(
	sanguis::server::entities::enemies::factory::parameters const &_parameters
)
{
	SANGUIS_SERVER_BUFFS_DEFINE_SPECIAL(
		skeleton_burn,
		burn
	);

	return
		fcppt::make_unique_ptr<
			sanguis::server::entities::enemies::enemy
		>(
			_parameters.diff_clock(),
			_parameters.enemy_type(),
			_parameters.load_context(),
			sanguis::server::damage::no_armor(),
			sanguis::server::health(
				500.f
			),
			sanguis::server::entities::movement_speed(
				50.f
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
					100.f
				),
				sanguis::server::weapons::base_cooldown(
					sanguis::duration_second(
						1.f
					)
				),
				sanguis::server::weapons::damage(
					10.f
				)
			),
			sanguis::server::pickup_probability(
				0.75f
			),
			sanguis::server::exp(
				300.f
			),
			_parameters.difficulty(),
			_parameters.spawn_owner(),
			fcppt::assign::make_container<
				sanguis::server::auras::container
			>(
				fcppt::make_unique_ptr<
					sanguis::server::auras::buff
				>(
					sanguis::server::radius(
						200.f
					),
					sanguis::server::team::monsters,
					sanguis::aura_type::burn,
					sanguis::server::auras::influence::debuff,
					sanguis::server::buffs::burn_create<
						skeleton_burn
					>(
						_parameters.diff_clock(),
						sanguis::server::buffs::burn_interval(
							sanguis::duration_second(
								1.f
							)
						),
						sanguis::server::damage::unit(
							1.f
						),
						sanguis::server::damage::list(
							sanguis::server::damage::fire =
								sanguis::server::damage::unit(
									1.f
								)
						)
					)
				)
			).move_container()
		);
}
