#include <sanguis/diff_clock_fwd.hpp>
#include <sanguis/secondary_weapon_type.hpp>
#include <sanguis/string_vector.hpp>
#include <sanguis/weapon_type.hpp>
#include <sanguis/server/direction.hpp>
#include <sanguis/server/radius.hpp>
#include <sanguis/server/damage/unit.hpp>
#include <sanguis/server/entities/insert_parameters.hpp>
#include <sanguis/server/entities/projectiles/grenade.hpp>
#include <sanguis/server/environment/insert_no_result.hpp>
#include <sanguis/server/environment/object.hpp>
#include <sanguis/server/weapons/aoe.hpp>
#include <sanguis/server/weapons/base_cooldown.hpp>
#include <sanguis/server/weapons/cast_point.hpp>
#include <sanguis/server/weapons/damage.hpp>
#include <sanguis/server/weapons/delayed_attack.hpp>
#include <sanguis/server/weapons/grenade.hpp>
#include <sanguis/server/weapons/make_attribute.hpp>
#include <sanguis/server/weapons/reload_time.hpp>
#include <sanguis/server/weapons/weapon.hpp>
#include <fcppt/insert_to_fcppt_string.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/text.hpp>


sanguis::server::weapons::grenade::grenade(
	sanguis::diff_clock const &_diff_clock,
	sanguis::server::weapons::base_cooldown const _base_cooldown,
	sanguis::server::weapons::damage const _damage,
	sanguis::server::weapons::aoe const _aoe,
	sanguis::server::weapons::cast_point const _cast_point,
	sanguis::server::weapons::reload_time const _reload_time,
	sanguis::server::weapons::range const _range
)
:
	sanguis::server::weapons::weapon(
		_diff_clock,
		sanguis::weapon_type(
			sanguis::secondary_weapon_type::grenade
		),
		_range,
		sanguis::server::weapons::magazine_size(
			1u
		),
		sanguis::server::weapons::magazine_count(
			1u
		),
		_base_cooldown,
		_cast_point,
		_reload_time
	),
	damage_(
		_damage
	),
	aoe_(
		_aoe
	)
{
}

sanguis::server::weapons::grenade::~grenade()
{
}

void
sanguis::server::weapons::grenade::do_attack(
	sanguis::server::weapons::delayed_attack const &_attack
)
{
	sanguis::server::environment::insert_no_result(
		_attack.environment(),
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
