#include "pistol.hpp"
#include "delayed_attack.hpp"
#include "../entities/entity.hpp"
#include "../entities/projectiles/simple_bullet.hpp"

sanguis::server::weapons::pistol::pistol(
	server::environment const &env,
	weapon_type::type const type_,
	time_type const base_cooldown,
	space_unit const damage,
	time_type const cast_point,
	unsigned const magazine_size,
	time_type const reload_time)
:
	weapon(
		env,
		type_,
		1000, // FIXME
		magazine_size,
		unlimited_magazine,
		base_cooldown,
		cast_point,
		reload_time
	),
	damage(damage)
{}

void sanguis::server::weapons::pistol::do_attack(
	delayed_attack const &a)
{
	insert(
		entities::auto_ptr(
			new entities::projectiles::simple_bullet(
				environment(),
				a.spawn_point(),
				a.angle(),
				a.team(),
				damage
			)
		)
	);
}
