#include "rocket_launcher.hpp"
#include "delayed_attack.hpp"
#include "unlimited_magazine_count.hpp"
#include "../entities/projectiles/rocket.hpp"

sanguis::server::weapons::rocket_launcher::rocket_launcher(
	server::environment const &env,
	weapon_type::type const type_,
	weapons::base_cooldown const base_cooldown_,
	space_unit const rocket_damage,
	space_unit const rocket_aoe,
	weapons::magazine_size const magazine_size_,
	weapons::reload_time const reload_time_
)
:
	weapon(
		env,
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
	rocket_damage(rocket_damage),
	rocket_aoe(rocket_aoe)
{}

void sanguis::server::weapons::rocket_launcher::do_attack(
	delayed_attack const &a)
{
	insert(
		entities::auto_ptr(
			new entities::projectiles::rocket(
				environment(),
				a.spawn_point(),
				a.angle(),
				a.team(),
				rocket_damage,
				rocket_aoe
			)
		)
	);
}
