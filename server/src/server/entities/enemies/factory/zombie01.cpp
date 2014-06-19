#include <sanguis/duration_second.hpp>
#include <sanguis/server/exp.hpp>
#include <sanguis/server/health.hpp>
#include <sanguis/server/pickup_probability.hpp>
#include <sanguis/server/ai/create_simple.hpp>
#include <sanguis/server/ai/sight_range.hpp>
#include <sanguis/server/auras/aura.hpp>
#include <sanguis/server/auras/container.hpp>
#include <sanguis/server/damage/full.hpp>
#include <sanguis/server/damage/list.hpp>
#include <sanguis/server/damage/no_armor.hpp>
#include <sanguis/server/damage/normal.hpp>
#include <sanguis/server/entities/base.hpp>
#include <sanguis/server/entities/movement_speed.hpp>
#include <sanguis/server/entities/unique_ptr.hpp>
#include <sanguis/server/entities/enemies/factory/make.hpp>
#include <sanguis/server/entities/enemies/factory/parameters.hpp>
#include <sanguis/server/entities/enemies/factory/zombie01.hpp>
#include <sanguis/server/weapons/base_cooldown.hpp>
#include <sanguis/server/weapons/damage.hpp>
#include <sanguis/server/weapons/melee.hpp>
#include <sanguis/server/weapons/range.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/config/external_begin.hpp>
#include <cmath>
#include <fcppt/config/external_end.hpp>


sanguis::server::entities::unique_ptr
sanguis::server::entities::enemies::factory::zombie01(
	sanguis::server::entities::enemies::factory::parameters const &_parameters
)
{
	return
		sanguis::server::entities::enemies::factory::make(
			_parameters,
			sanguis::server::damage::no_armor(),
			sanguis::server::health(
				10.f
				*
				std::sqrt(
					_parameters.difficulty().get()
				)
			),
			sanguis::server::entities::movement_speed(
				200.f
			),
			sanguis::server::ai::create_simple(
				sanguis::server::ai::sight_range(
					1000.f
				)
			),
			fcppt::make_unique_ptr<
				sanguis::server::weapons::melee
			>(
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
					*
					std::sqrt(
						_parameters.difficulty().get()
					)
				),
				sanguis::server::damage::list{
					sanguis::server::damage::normal =
						sanguis::server::damage::full
				}
			),
			sanguis::server::pickup_probability(
				0.25f
			),
			sanguis::server::exp(
				5.f
			),
			sanguis::server::auras::container()
		);
}
