#include <sanguis/duration_second.hpp>
#include <sanguis/server/exp.hpp>
#include <sanguis/server/health.hpp>
#include <sanguis/server/pickup_probability.hpp>
#include <sanguis/server/team.hpp>
#include <sanguis/server/radius.hpp>
#include <sanguis/server/ai/create_simple.hpp>
#include <sanguis/server/ai/sight_range.hpp>
#include <sanguis/server/auras/container.hpp>
#include <sanguis/server/auras/slow_create.hpp>
#include <sanguis/server/buffs/define_special.hpp>
#include <sanguis/server/buffs/slow.hpp>
#include <sanguis/server/buffs/slow_factor.hpp>
#include <sanguis/server/damage/full.hpp>
#include <sanguis/server/damage/ice.hpp>
#include <sanguis/server/damage/list.hpp>
#include <sanguis/server/damage/no_armor.hpp>
#include <sanguis/server/entities/base.hpp>
#include <sanguis/server/entities/movement_speed.hpp>
#include <sanguis/server/entities/unique_ptr.hpp>
#include <sanguis/server/entities/enemies/factory/ghost.hpp>
#include <sanguis/server/entities/enemies/factory/make.hpp>
#include <sanguis/server/entities/enemies/factory/parameters.hpp>
#include <sanguis/server/weapons/base_cooldown.hpp>
#include <sanguis/server/weapons/damage.hpp>
#include <sanguis/server/weapons/melee.hpp>
#include <sanguis/server/weapons/range.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/assign/make_container.hpp>
#include <fcppt/config/external_begin.hpp>
#include <cmath>
#include <fcppt/config/external_end.hpp>


sanguis::server::entities::unique_ptr
sanguis::server::entities::enemies::factory::ghost(
	sanguis::server::entities::enemies::factory::parameters const &_parameters
)
{
	SANGUIS_SERVER_BUFFS_DEFINE_SPECIAL(
		ghost_slow,
		slow
	);

	return
		sanguis::server::entities::enemies::factory::make(
			_parameters,
			sanguis::server::damage::no_armor(),
			sanguis::server::health(
				6.f
				*
				std::sqrt(
					_parameters.difficulty().get()
				)
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
				_parameters.random_generator(),
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
				),
				sanguis::server::damage::list{
					sanguis::server::damage::ice =
						sanguis::server::damage::full
				}
			),
			sanguis::server::pickup_probability(
				0.1f
			),
			sanguis::server::exp(
				10.f
			),
			fcppt::assign::make_container<
				sanguis::server::auras::container
			>(
				sanguis::server::auras::slow_create<
					ghost_slow
				>(
					sanguis::server::radius(
						200.f
					),
					sanguis::server::team::monsters,
					sanguis::server::buffs::slow_factor(
						0.1f
					)
				)
			).move_container()
		);
}
