#include <sanguis/diff_clock_fwd.hpp>
#include <sanguis/duration_second.hpp>
#include <sanguis/weapon_type.hpp>
#include <sanguis/server/direction.hpp>
#include <sanguis/server/radius.hpp>
#include <sanguis/server/entities/projectiles/rocket.hpp>
#include <sanguis/server/entities/insert_parameters.hpp>
#include <sanguis/server/environment/object.hpp>
#include <sanguis/server/weapons/aoe.hpp>
#include <sanguis/server/weapons/base_cooldown.hpp>
#include <sanguis/server/weapons/cast_point.hpp>
#include <sanguis/server/weapons/damage.hpp>
#include <sanguis/server/weapons/delayed_attack.hpp>
#include <sanguis/server/weapons/magazine_size.hpp>
#include <sanguis/server/weapons/range.hpp>
#include <sanguis/server/weapons/reload_time.hpp>
#include <sanguis/server/weapons/rocket_launcher.hpp>
#include <sanguis/server/weapons/unlimited_magazine_count.hpp>
#include <sanguis/server/weapons/weapon.hpp>
#include <fcppt/make_unique_ptr.hpp>


sanguis::server::weapons::rocket_launcher::rocket_launcher(
	sanguis::diff_clock const &_diff_clock,
	sanguis::weapon_type const _type,
	sanguis::server::weapons::base_cooldown const _base_cooldown,
	sanguis::server::weapons::damage const _damage,
	sanguis::server::weapons::aoe const _aoe,
	sanguis::server::weapons::magazine_size const _magazine_size,
	sanguis::server::weapons::reload_time const _reload_time
)
:
	sanguis::server::weapons::weapon(
		_diff_clock,
		_type,
		sanguis::server::weapons::range(
			20.f
		), // FIXME
		_magazine_size,
		sanguis::server::weapons::unlimited_magazine_count,
		_base_cooldown,
		sanguis::server::weapons::cast_point(
			sanguis::duration_second(
				0.5f
			)
		), // FIXME
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

sanguis::server::weapons::rocket_launcher::~rocket_launcher()
{
}

void
sanguis::server::weapons::rocket_launcher::do_attack(
	sanguis::server::weapons::delayed_attack const &_attack
)
{
	_attack.environment().insert(
		fcppt::make_unique_ptr<
			sanguis::server::entities::projectiles::rocket
		>(
			this->diff_clock(),
			_attack.environment().load_context(),
			_attack.team(),
			damage_,
			sanguis::server::radius(
				aoe_.get()
			),
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
