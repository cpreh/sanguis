#include <sanguis/diff_clock_fwd.hpp>
#include <sanguis/random_generator_fwd.hpp>
#include <sanguis/secondary_weapon_type.hpp>
#include <sanguis/string_vector.hpp>
#include <sanguis/weapon_type.hpp>
#include <sanguis/server/direction.hpp>
#include <sanguis/server/radius.hpp>
#include <sanguis/server/damage/unit.hpp>
#include <sanguis/server/entities/insert_parameters.hpp>
#include <sanguis/server/entities/projectiles/grenade.hpp>
#include <sanguis/server/environment/object.hpp>
#include <sanguis/server/weapons/accuracy.hpp>
#include <sanguis/server/weapons/attack_result.hpp>
#include <sanguis/server/weapons/delayed_attack.hpp>
#include <sanguis/server/weapons/grenade.hpp>
#include <sanguis/server/weapons/grenade_parameters.hpp>
#include <sanguis/server/weapons/insert_to_attack_result.hpp>
#include <sanguis/server/weapons/make_attribute.hpp>
#include <sanguis/server/weapons/optional_magazine_size.hpp>
#include <sanguis/server/weapons/optional_reload_time.hpp>
#include <sanguis/server/weapons/weapon.hpp>
#include <fcppt/insert_to_fcppt_string.hpp>
#include <fcppt/literal.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/text.hpp>


sanguis::server::weapons::grenade::grenade(
	sanguis::diff_clock const &_diff_clock,
	sanguis::random_generator &_random_generator,
	sanguis::server::weapons::grenade_parameters const &_parameters
)
:
	sanguis::server::weapons::weapon(
		_diff_clock,
		_random_generator,
		sanguis::weapon_type(
			sanguis::secondary_weapon_type::grenade
		),
		sanguis::server::weapons::accuracy(
			fcppt::literal<
				sanguis::server::weapons::accuracy::value_type
			>(
				1
			)
		),
		_parameters.range(),
		sanguis::server::weapons::optional_magazine_size(
			_parameters.magazine_size()
		),
		_parameters.base_cooldown(),
		_parameters.cast_point(),
		sanguis::server::weapons::optional_reload_time()
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
{
}

sanguis::server::weapons::attack_result
sanguis::server::weapons::grenade::do_attack(
	sanguis::server::weapons::delayed_attack const &_attack
)
{
	return
		sanguis::server::weapons::insert_to_attack_result(
			_attack.environment().insert(
				fcppt::make_unique_ptr<
					sanguis::server::entities::projectiles::grenade
				>(
					this->diff_clock(),
					_attack.environment().load_context(),
					_attack.team(),
					sanguis::server::damage::unit(
						damage_
					),
					sanguis::server::radius(
						aoe_.get()
					),
					_attack.target().get(),
					sanguis::server::direction(
						_attack.angle().get()
					)
				),
				sanguis::server::entities::insert_parameters(
					_attack.spawn_point(),
					_attack.angle()
				)
			)
		);
}

sanguis::string_vector
sanguis::server::weapons::grenade::attributes() const
{
	return
		sanguis::string_vector{
			sanguis::server::weapons::make_attribute(
				FCPPT_TEXT("damage"),
				fcppt::insert_to_fcppt_string(
					damage_
				)
			),
			sanguis::server::weapons::make_attribute(
				FCPPT_TEXT("aoe"),
				fcppt::insert_to_fcppt_string(
					aoe_
				)
			)
		};
}
