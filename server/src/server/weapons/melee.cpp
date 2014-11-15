#include <sanguis/duration_second.hpp>
#include <sanguis/primary_weapon_type.hpp>
#include <sanguis/random_generator_fwd.hpp>
#include <sanguis/weapon_attribute_vector.hpp>
#include <sanguis/weapon_type.hpp>
#include <sanguis/server/center.hpp>
#include <sanguis/server/entities/base.hpp>
#include <sanguis/server/entities/insert_parameters_center.hpp>
#include <sanguis/server/entities/modify_damages.hpp>
#include <sanguis/server/entities/with_weapon.hpp>
#include <sanguis/server/entities/projectiles/melee.hpp>
#include <sanguis/server/environment/insert_no_result.hpp>
#include <sanguis/server/weapons/attack.hpp>
#include <sanguis/server/weapons/attack_result.hpp>
#include <sanguis/server/weapons/cast_point.hpp>
#include <sanguis/server/weapons/melee.hpp>
#include <sanguis/server/weapons/melee_parameters.hpp>
#include <sanguis/server/weapons/optional_reload_time.hpp>
#include <sanguis/server/weapons/parameters.hpp>
#include <sanguis/server/weapons/weapon.hpp>
#include <sanguis/server/weapons/attributes/make_damage.hpp>
#include <sanguis/server/weapons/attributes/optional_accuracy.hpp>
#include <sanguis/server/weapons/attributes/optional_magazine_size.hpp>
#include <fcppt/make_unique_ptr.hpp>


sanguis::server::weapons::melee::melee(
	sanguis::random_generator &_random_generator,
	sanguis::server::weapons::melee_parameters const &_parameters
)
:
	sanguis::server::weapons::weapon(
		sanguis::server::weapons::parameters{
			_random_generator,
			sanguis::weapon_type(
				sanguis::primary_weapon_type::melee
			),
			sanguis::server::weapons::attributes::optional_accuracy(),
			_parameters.range(),
			sanguis::server::weapons::attributes::optional_magazine_size(),
			_parameters.backswing_time(),
			sanguis::server::weapons::cast_point(
				sanguis::duration_second(
					0.f
				)
			),
			sanguis::server::weapons::optional_reload_time()
		}
	),
	damage_{
		_parameters.damage()
	},
	damage_values_(
		_parameters.damage_values()
	)
{
}

sanguis::server::weapons::melee::~melee()
{
}

sanguis::server::weapons::attack_result
sanguis::server::weapons::melee::do_attack(
	sanguis::server::weapons::attack const &_attack
)
{
	sanguis::server::environment::insert_no_result(
		_attack.environment(),
		fcppt::make_unique_ptr<
			sanguis::server::entities::projectiles::melee
		>(
			this->owner().team(),
			damage_.value(),
			sanguis::server::entities::modify_damages(
				this->owner(),
				damage_values_
			)
		),
		sanguis::server::entities::insert_parameters_center(
			sanguis::server::center(
				_attack.target().get()
			)
		)
	);

	return
		sanguis::server::weapons::attack_result::success;
}

sanguis::weapon_attribute_vector
sanguis::server::weapons::melee::attributes() const
{
	return
		sanguis::weapon_attribute_vector{
			sanguis::server::weapons::attributes::make_damage(
				damage_
			)
		};
}
