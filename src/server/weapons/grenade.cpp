#include <sanguis/diff_clock_fwd.hpp>
#include <sanguis/weapon_type.hpp>
#include <sanguis/server/direction.hpp>
#include <sanguis/server/radius.hpp>
#include <sanguis/server/damage/unit.hpp>
#include <sanguis/server/entities/insert_parameters.hpp>
#include <sanguis/server/entities/projectiles/grenade.hpp>
#include <sanguis/server/environment/object.hpp>
#include <sanguis/server/weapons/aoe.hpp>
#include <sanguis/server/weapons/base_cooldown.hpp>
#include <sanguis/server/weapons/cast_point.hpp>
#include <sanguis/server/weapons/damage.hpp>
#include <sanguis/server/weapons/delayed_attack.hpp>
#include <sanguis/server/weapons/grenade.hpp>
#include <sanguis/server/weapons/reload_time.hpp>
#include <sanguis/server/weapons/weapon.hpp>
#include <fcppt/make_unique_ptr.hpp>


sanguis::server::weapons::grenade::grenade(
	sanguis::diff_clock const &_diff_clock,
	sanguis::weapon_type const _type,
	sanguis::server::weapons::base_cooldown const _base_cooldown,
	sanguis::server::weapons::damage const _damage,
	sanguis::server::weapons::aoe const _aoe,
	sanguis::server::weapons::cast_point const _cast_point,
	sanguis::server::weapons::reload_time const _reload_time
)
:
	sanguis::server::weapons::weapon(
		_diff_clock,
		_type,
		sanguis::server::weapons::range(20.f), // FIXME
		sanguis::server::weapons::magazine_size(1u),
		sanguis::server::weapons::magazine_count(1u),
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
			_attack.dest(),
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
