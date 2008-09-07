#include "rocket_launcher.hpp"
#include "delayed_attack.hpp"
#include "../entities/projectiles/rocket.hpp"

sanguis::server::weapons::rocket_launcher::rocket_launcher(
	environment const &env,
	weapon_type::type const type_,
	time_type const base_cooldown,
	space_unit const rocket_damage,
	space_unit const rocket_aoe)
:
	weapon(
		env,
		type_,
		1000, // FIXME
		base_cooldown,
		static_cast<time_type>(
			0.5)), // FIXME
	rocket_damage(rocket_damage),
	rocket_aoe(rocket_aoe)
{}

void sanguis::server::weapons::rocket_launcher::do_attack(
	delayed_attack const &a)
{
	insert(
		entities::auto_ptr(
			new entities::projectiles::rocket(
				get_environment(),
				a.spawn_point(),
				a.angle(),
				a.team(),
				rocket_damage,
				rocket_aoe)));
}
