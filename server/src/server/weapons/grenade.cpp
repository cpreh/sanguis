#include <sanguis/duration_second.hpp>
#include <sanguis/secondary_weapon_type.hpp>
#include <sanguis/weapon_attribute_vector.hpp>
#include <sanguis/weapon_type.hpp>
#include <sanguis/server/direction.hpp>
#include <sanguis/server/damage/explosive.hpp>
#include <sanguis/server/damage/unit.hpp>
#include <sanguis/server/entities/insert_parameters.hpp>
#include <sanguis/server/entities/modify_damages.hpp>
#include <sanguis/server/entities/with_id.hpp>
#include <sanguis/server/entities/with_weapon.hpp>
#include <sanguis/server/entities/projectiles/grenade.hpp>
#include <sanguis/server/environment/object.hpp>
#include <sanguis/server/weapons/attack.hpp>
#include <sanguis/server/weapons/attack_result.hpp>
#include <sanguis/server/weapons/common_parameters_fwd.hpp>
#include <sanguis/server/weapons/grenade.hpp>
#include <sanguis/server/weapons/grenade_parameters.hpp>
#include <sanguis/server/weapons/insert_to_attack_result.hpp>
#include <sanguis/server/weapons/magazine_size.hpp>
#include <sanguis/server/weapons/optional_reload_time.hpp>
#include <sanguis/server/weapons/parameters.hpp>
#include <sanguis/server/weapons/reload_time.hpp>
#include <sanguis/server/weapons/unique_ptr.hpp>
#include <sanguis/server/weapons/weapon.hpp>
#include <sanguis/server/weapons/attributes/aoe.hpp>
#include <sanguis/server/weapons/attributes/damage.hpp>
#include <sanguis/server/weapons/attributes/magazine_size.hpp>
#include <sanguis/server/weapons/attributes/make_aoe.hpp>
#include <sanguis/server/weapons/attributes/make_damage.hpp>
#include <sanguis/server/weapons/attributes/optional_accuracy.hpp>
#include <sanguis/server/weapons/attributes/optional_magazine_size.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/unique_ptr_to_base.hpp>


sanguis::server::weapons::grenade::grenade(
	sanguis::server::weapons::common_parameters const &_common_parameters,
	sanguis::server::weapons::grenade_parameters const &_parameters
)
:
	sanguis::server::weapons::weapon(
		sanguis::server::weapons::parameters{
			_common_parameters,
			sanguis::weapon_type(
				sanguis::secondary_weapon_type::grenade
			),
			sanguis::server::weapons::attributes::optional_accuracy(),
			_parameters.range(),
			sanguis::server::weapons::attributes::optional_magazine_size(
				sanguis::server::weapons::attributes::magazine_size{
					sanguis::server::weapons::magazine_size{
						1U
					}
				}
			),
			_parameters.backswing_time(),
			_parameters.cast_point(),
			sanguis::server::weapons::optional_reload_time(
				sanguis::server::weapons::reload_time(
					sanguis::duration_second(
						10.F // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
					)
				)
			)
		}
	),
	damage_(
		_parameters.damage()
	),
	aoe_(
		_parameters.aoe()
	)
{
}

sanguis::server::weapons::grenade::~grenade()
= default;

sanguis::server::weapons::grenade::grenade(
	sanguis::server::weapons::parameters const &_parameters,
	sanguis::server::weapons::attributes::damage const _damage,
	sanguis::server::weapons::attributes::aoe const _aoe
)
:
	sanguis::server::weapons::weapon{
		_parameters
	},
	damage_{
		_damage
	},
	aoe_{
		_aoe
	}
{
}

sanguis::server::weapons::unique_ptr
sanguis::server::weapons::grenade::clone() const
{
	return
		fcppt::unique_ptr_to_base<
			sanguis::server::weapons::weapon
		>(
			fcppt::make_unique_ptr<
				sanguis::server::weapons::grenade
			>(
				this->parameters(),
				damage_,
				aoe_
			)
		);
}

sanguis::server::weapons::attack_result
sanguis::server::weapons::grenade::do_attack(
	sanguis::server::weapons::attack const &_attack
)
{
	return
		sanguis::server::weapons::insert_to_attack_result(
			_attack.environment().insert(
				fcppt::unique_ptr_to_base<
					sanguis::server::entities::with_id
				>(
					fcppt::make_unique_ptr<
						sanguis::server::entities::projectiles::grenade
					>(
						_attack.environment().load_context(),
						this->owner().team(),
						damage_.value(),
						sanguis::server::entities::modify_damages(
							this->owner(),
							sanguis::server::damage::explosive()
						),
						aoe_.value(),
						_attack.target().get(),
						sanguis::server::direction(
							_attack.angle().get()
						)
					)
				),
				sanguis::server::entities::insert_parameters(
					this->owner().center(),
					_attack.angle()
				)
			)
		);
}

sanguis::weapon_attribute_vector
sanguis::server::weapons::grenade::attributes() const
{
	return
		sanguis::weapon_attribute_vector{
			sanguis::server::weapons::attributes::make_damage(
				damage_
			),
			sanguis::server::weapons::attributes::make_aoe(
				aoe_
			)
		};
}
