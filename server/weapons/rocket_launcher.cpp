#include "rocket_launcher.hpp"
#include "delayed_attack.hpp"
#include "unlimited_magazine_count.hpp"
#include "../entities/projectiles/rocket.hpp"
#include "../entities/insert_parameters.hpp"
#include "../environment/object.hpp"

sanguis::server::weapons::rocket_launcher::rocket_launcher(
	weapon_type::type const type_,
	weapons::base_cooldown const base_cooldown_,
	weapons::damage const damage_,
	weapons::aoe const aoe_,
	weapons::magazine_size const magazine_size_,
	weapons::reload_time const reload_time_
)
:
	weapon(
		type_,
		weapons::range(1000), // FIXME
		magazine_size_,
		unlimited_magazine_count,
		base_cooldown_,
		weapons::cast_point(
			0.5f
		), // FIXME
		reload_time_
	),
	damage_(damage_),
	aoe_(aoe_)
{}

void
sanguis::server::weapons::rocket_launcher::do_attack(
	delayed_attack const &a
)
{
	a.environment()->insert(
		entities::auto_ptr(
			new entities::projectiles::rocket(
				a.environment()->load_context(),
				a.team(),
				server::damage::unit(
					damage_
				),
				aoe_,
				a.angle()
			)
		),
		entities::insert_parameters(
			a.spawn_point(),
			a.angle()
		)
	);
}
