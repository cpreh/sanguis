#include <sanguis/duration_second.hpp>
#include <sanguis/server/exp.hpp>
#include <sanguis/server/health.hpp>
#include <sanguis/server/mass.hpp>
#include <sanguis/server/pickup_probability.hpp>
#include <sanguis/server/ai/create_simple.hpp>
#include <sanguis/server/ai/sight_range.hpp>
#include <sanguis/server/auras/aura.hpp>
#include <sanguis/server/auras/container.hpp>
#include <sanguis/server/damage/full.hpp>
#include <sanguis/server/damage/make_array.hpp>
#include <sanguis/server/damage/no_armor.hpp>
#include <sanguis/server/damage/normal.hpp>
#include <sanguis/server/entities/movement_speed.hpp>
#include <sanguis/server/entities/with_id.hpp>
#include <sanguis/server/entities/with_id_unique_ptr.hpp>
#include <sanguis/server/entities/enemies/attribute_container.hpp>
#include <sanguis/server/entities/enemies/is_unique.hpp>
#include <sanguis/server/entities/enemies/parameters.hpp>
#include <sanguis/server/entities/enemies/special.hpp>
#include <sanguis/server/entities/enemies/factory/parameters.hpp>
#include <sanguis/server/entities/enemies/factory/reaper.hpp>
#include <sanguis/server/entities/enemies/modifiers/parameters.hpp>
#include <sanguis/server/entities/enemies/modifiers/regenerating.hpp>
#include <sanguis/server/entities/enemies/skills/factory/container.hpp>
#include <sanguis/server/entities/enemies/skills/factory/scatter.hpp>
#include <sanguis/server/weapons/backswing_time.hpp>
#include <sanguis/server/weapons/damage.hpp>
#include <sanguis/server/weapons/melee.hpp>
#include <sanguis/server/weapons/melee_parameters.hpp>
#include <sanguis/server/weapons/range.hpp>
#include <sanguis/server/weapons/weapon.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/unique_ptr_to_base.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/units/systems/si/mass.hpp>
#include <cmath>
#include <functional>
#include <utility>
#include <fcppt/config/external_end.hpp>


sanguis::server::entities::with_id_unique_ptr
sanguis::server::entities::enemies::factory::reaper(
	sanguis::server::entities::enemies::factory::parameters const &_parameters
)
{
	sanguis::server::entities::enemies::parameters enemy_parameters(
		_parameters.enemy_type(),
		_parameters.load_context(),
		sanguis::server::damage::no_armor(),
		sanguis::server::mass{
			10.f
			*
			boost::units::si::kilogram
		},
		sanguis::server::health(
			100.f
			*
			std::sqrt(
				_parameters.difficulty().get()
			)
		),
		sanguis::server::entities::movement_speed(
			150.f
		),
		sanguis::server::ai::create_simple(
			_parameters.random_generator(),
			sanguis::server::ai::sight_range(
				1000.f
			)
		),
		fcppt::unique_ptr_to_base<
			sanguis::server::weapons::weapon
		>(
			fcppt::make_unique_ptr<
				sanguis::server::weapons::melee
			>(
				_parameters.random_generator(),
				sanguis::server::weapons::melee_parameters{
					sanguis::server::weapons::range(
						75.f
					),
					sanguis::server::weapons::backswing_time(
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
					sanguis::server::damage::make_array({
						sanguis::server::damage::normal =
							sanguis::server::damage::full
					})
				}
			)
		),
		sanguis::server::pickup_probability(
			0.f
		),
		sanguis::server::exp(
			0.f
		),
		_parameters.difficulty(),
		_parameters.spawn_owner(),
		sanguis::server::auras::container(
			// TODO
		)
	);

	sanguis::server::entities::enemies::modifiers::parameters const modifiers_parameters(
		_parameters.random_generator()
	);

	return
		fcppt::unique_ptr_to_base<
			sanguis::server::entities::with_id
		>(
			fcppt::make_unique_ptr<
				sanguis::server::entities::enemies::special
			>(
				_parameters.random_generator(),
				std::move(
					enemy_parameters
				),
				sanguis::server::entities::enemies::attribute_container{
					sanguis::server::entities::enemies::modifiers::regenerating(
						enemy_parameters,
						modifiers_parameters
					)
				},
				sanguis::server::entities::enemies::skills::factory::container{
					sanguis::server::entities::enemies::skills::factory::scatter
				},
				sanguis::server::entities::enemies::is_unique{
					true
				}
			)
		);
}
