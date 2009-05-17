#include "grenade.hpp"
#include "delayed_attack.hpp"
#include "../entities/entity.hpp"
#include "../entities/projectiles/grenade.hpp"

sanguis::server::weapons::grenade::grenade(
	server::environment const &env,
	weapon_type::type const type_,
	time_type const base_cooldown,
	space_unit const damage,
	space_unit const radius,
	time_type const cast_point,
	time_type const reload_time)
:
	weapon(
		env,
		type_,
		1000, // FIXME
		1, // magazine size
		1, // number of magazine at start
		base_cooldown,
		cast_point,
		reload_time
	),
	damage(damage),
	radius(radius)
{}

void
sanguis::server::weapons::grenade::do_attack(
	delayed_attack const &a)
{
	insert(
		entities::auto_ptr(
			new entities::projectiles::grenade(
				environment(),
				a.spawn_point(),
				a.angle(),
				a.team(),
				damage,
				radius
			)
		)
	);
}
