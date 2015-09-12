#include <sanguis/duration_second.hpp>
#include <sanguis/primary_weapon_type.hpp>
#include <sanguis/weapon_type.hpp>
#include <sanguis/server/exp.hpp>
#include <sanguis/server/health.hpp>
#include <sanguis/server/mass.hpp>
#include <sanguis/server/pickup_probability.hpp>
#include <sanguis/server/ai/create_simple.hpp>
#include <sanguis/server/ai/sight_range.hpp>
#include <sanguis/server/auras/aura.hpp>
#include <sanguis/server/auras/container.hpp>
#include <sanguis/server/damage/no_armor.hpp>
#include <sanguis/server/entities/movement_speed.hpp>
#include <sanguis/server/entities/with_id.hpp>
#include <sanguis/server/entities/with_id_unique_ptr.hpp>
#include <sanguis/server/entities/enemies/factory/make.hpp>
#include <sanguis/server/entities/enemies/factory/parameters.hpp>
#include <sanguis/server/entities/enemies/factory/zombie00.hpp>
#include <sanguis/server/weapons/accuracy.hpp>
#include <sanguis/server/weapons/backswing_time.hpp>
#include <sanguis/server/weapons/cast_point.hpp>
#include <sanguis/server/weapons/damage.hpp>
#include <sanguis/server/weapons/magazine_size.hpp>
#include <sanguis/server/weapons/pistol.hpp>
#include <sanguis/server/weapons/pistol_parameters.hpp>
#include <sanguis/server/weapons/range.hpp>
#include <sanguis/server/weapons/reload_time.hpp>
#include <sanguis/server/weapons/weapon.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/unique_ptr_to_base.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/units/systems/si/mass.hpp>
#include <cmath>
#include <fcppt/config/external_end.hpp>


sanguis::server::entities::with_id_unique_ptr
sanguis::server::entities::enemies::factory::zombie00(
	sanguis::server::entities::enemies::factory::parameters const &_parameters
)
{
	return
		sanguis::server::entities::enemies::factory::make(
			_parameters,
			sanguis::server::damage::no_armor(),
			sanguis::server::mass{
				10.f
				*
				boost::units::si::kilogram
			},
			sanguis::server::health(
				9.f
				*
				std::sqrt(
					_parameters.difficulty().get()
				)
			),
			sanguis::server::entities::movement_speed(
				25.f
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
					sanguis::server::weapons::pistol
				>(
					_parameters.random_generator(),
					sanguis::weapon_type(
						sanguis::primary_weapon_type::pistol
					),
					sanguis::server::weapons::pistol_parameters(
						sanguis::server::weapons::accuracy(
							0.9f
						),
						sanguis::server::weapons::backswing_time(
							sanguis::duration_second(
								1.f
							)
						),
						sanguis::server::weapons::damage(
							10.f
						),
						sanguis::server::weapons::cast_point(
							sanguis::duration_second(
								0
							)
						),
						sanguis::server::weapons::magazine_size(
							5u
						),
						sanguis::server::weapons::reload_time(
							sanguis::duration_second(
								5.f
							)
						),
						sanguis::server::weapons::range(
							1000.f
						)
					)
				)
			),
			sanguis::server::pickup_probability(
				0.25f
			),
			sanguis::server::exp(
				10.f
			),
			sanguis::server::auras::container()
		);
}
