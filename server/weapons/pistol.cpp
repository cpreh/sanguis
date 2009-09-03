#include "pistol.hpp"
#include "delayed_attack.hpp"
#include "unlimited_magazine_count.hpp"
#include "../entities/entity.hpp"
#include "../entities/projectiles/simple_bullet.hpp"

sanguis::server::weapons::pistol::pistol(
	server::environment const &env,
	weapon_type::type const type_,
	weapons::base_cooldown const base_cooldown_,
	space_unit const damage,
	weapons::cast_point const cast_point_,
	weapons::magazine_size const magazine_size_,
	weapons::reload_time const reload_time_,
	weapons::range const range_
)
:
	weapon(
		env,
		type_,
		range_,
		magazine_size_,
		unlimited_magazine_count,
		base_cooldown_,
		cast_point_,
		reload_time_
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
