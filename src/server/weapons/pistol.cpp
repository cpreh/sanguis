#include <sanguis/server/weapons/pistol.hpp>
#include <sanguis/server/weapons/delayed_attack.hpp>
#include <sanguis/server/weapons/unlimited_magazine_count.hpp>
#include <sanguis/server/entities/base.hpp>
#include <sanguis/server/entities/insert_parameters.hpp>
#include <sanguis/server/entities/projectiles/simple_bullet.hpp>
#include <sanguis/server/environment/object.hpp>
#include <fcppt/cref.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/ref.hpp>

sanguis::server::weapons::pistol::pistol(
	sanguis::diff_clock const &_diff_clock,
	weapon_type::type const _type,
	weapons::base_cooldown const _base_cooldown,
	weapons::damage const _damage,
	weapons::cast_point const _cast_point,
	weapons::magazine_size const _magazine_size,
	weapons::reload_time const _reload_time,
	weapons::range const _range
)
:
	weapon(
		_diff_clock,
		_type,
		_range,
		_magazine_size,
		unlimited_magazine_count,
		_base_cooldown,
		_cast_point,
		_reload_time
	),
	damage_(
		_damage
	)
{
}

sanguis::server::weapons::pistol::~pistol()
{
}

void
sanguis::server::weapons::pistol::do_attack(
	delayed_attack const &_attack
)
{
	_attack.environment().insert(
		entities::unique_ptr(
			fcppt::make_unique_ptr<
				entities::projectiles::simple_bullet
			>(
				fcppt::cref(
					this->diff_clock()
				),
				fcppt::ref(
					_attack.environment().load_context()
				),
				_attack.team(),
				damage_,
				server::direction(
					_attack.angle().get()
				)
			)
		),
		entities::insert_parameters(
			_attack.spawn_point(),
			_attack.angle()
		)
	);
}
