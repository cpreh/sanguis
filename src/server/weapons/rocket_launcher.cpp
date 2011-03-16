#include "rocket_launcher.hpp"
#include "delayed_attack.hpp"
#include "unlimited_magazine_count.hpp"
#include "../entities/projectiles/rocket.hpp"
#include "../entities/insert_parameters.hpp"
#include "../environment/object.hpp"
#include <fcppt/make_unique_ptr.hpp>

sanguis::server::weapons::rocket_launcher::rocket_launcher(
	weapon_type::type const _type,
	weapons::base_cooldown const _base_cooldown,
	weapons::damage const _damage,
	weapons::aoe const _aoe,
	weapons::magazine_size const _magazine_size,
	weapons::reload_time const _reload_time
)
:
	weapon(
		_type,
		weapons::range(1000), // FIXME
		_magazine_size,
		unlimited_magazine_count,
		_base_cooldown,
		weapons::cast_point(
			0.5f
		), // FIXME
		_reload_time
	),
	damage_(_damage),
	aoe_(_aoe)
{
}

sanguis::server::weapons::rocket_launcher::~rocket_launcher()
{
}

void
sanguis::server::weapons::rocket_launcher::do_attack(
	delayed_attack const &_attack
)
{
	_attack.environment()->insert(
		entities::unique_ptr(
			fcppt::make_unique_ptr<
				entities::projectiles::rocket
			>(
				_attack.environment()->load_context(),
				_attack.team(),
				server::damage::unit(
					damage_
				),
				aoe_.get(),
				_attack.angle()
			)
		),
		entities::insert_parameters(
			_attack.spawn_point(),
			_attack.angle()
		)
	);
}
