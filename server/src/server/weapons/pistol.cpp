#include <sanguis/random_generator_fwd.hpp>
#include <sanguis/weapon_attribute_vector.hpp>
#include <sanguis/weapon_type.hpp>
#include <sanguis/server/damage/full.hpp>
#include <sanguis/server/damage/make_array.hpp>
#include <sanguis/server/damage/piercing.hpp>
#include <sanguis/server/entities/base.hpp>
#include <sanguis/server/entities/insert_parameters.hpp>
#include <sanguis/server/entities/modify_damages.hpp>
#include <sanguis/server/entities/with_weapon.hpp>
#include <sanguis/server/entities/projectiles/simple_bullet.hpp>
#include <sanguis/server/environment/insert_no_result.hpp>
#include <sanguis/server/environment/object.hpp>
#include <sanguis/server/weapons/attack.hpp>
#include <sanguis/server/weapons/attack_result.hpp>
#include <sanguis/server/weapons/backswing_time.hpp>
#include <sanguis/server/weapons/optional_reload_time.hpp>
#include <sanguis/server/weapons/pistol.hpp>
#include <sanguis/server/weapons/pistol_parameters.hpp>
#include <sanguis/server/weapons/weapon.hpp>
#include <sanguis/server/weapons/attributes/make_damage.hpp>
#include <sanguis/server/weapons/attributes/optional_accuracy.hpp>
#include <sanguis/server/weapons/attributes/optional_magazine_size.hpp>
#include <fcppt/make_unique_ptr.hpp>


sanguis::server::weapons::pistol::pistol(
	sanguis::random_generator &_random_generator,
	sanguis::weapon_type const _weapon_type,
	sanguis::server::weapons::pistol_parameters const &_parameters
)
:
	sanguis::server::weapons::weapon(
		_random_generator,
		_weapon_type,
		sanguis::server::weapons::attributes::optional_accuracy(
			_parameters.accuracy()
		),
		_parameters.range(),
		sanguis::server::weapons::attributes::optional_magazine_size(
			_parameters.magazine_size()
		),
		_parameters.backswing_time(),
		_parameters.cast_point(),
		sanguis::server::weapons::optional_reload_time(
			_parameters.reload_time()
		)
	),
	damage_(
		_parameters.damage()
	)
{
}

sanguis::server::weapons::pistol::~pistol()
{
}

sanguis::server::weapons::attack_result
sanguis::server::weapons::pistol::do_attack(
	sanguis::server::weapons::attack const &_attack
)
{
	sanguis::server::environment::insert_no_result(
		_attack.environment(),
		fcppt::make_unique_ptr<
			sanguis::server::entities::projectiles::simple_bullet
		>(
			_attack.environment().load_context(),
			this->owner().team(),
			damage_.value(),
			sanguis::server::entities::modify_damages(
				this->owner(),
				sanguis::server::damage::make_array({
					sanguis::server::damage::piercing =
						sanguis::server::damage::full
				})
			),
			sanguis::server::direction(
				_attack.angle().get()
			)
		),
		sanguis::server::entities::insert_parameters(
			this->owner().center(),
			_attack.angle()
		)
	);

	return
		sanguis::server::weapons::attack_result::success;
}

sanguis::weapon_attribute_vector
sanguis::server::weapons::pistol::attributes() const
{
	return
		sanguis::weapon_attribute_vector{
			sanguis::server::weapons::attributes::make_damage(
				damage_
			)
		};
}
