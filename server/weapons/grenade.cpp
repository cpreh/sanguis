#include "grenade.hpp"
#include "delayed_attack.hpp"
#include "../entities/entity.hpp"
#include "../entities/projectiles/grenade.hpp"

sanguis::server::weapons::grenade::grenade(
	server::environment const &env,
	weapon_type::type const type_,
	weapons::base_cooldown const base_cooldown_,
	weapons::damage const damage_,
	weapons::aoe const aoe_,
	weapons::cast_point const cast_point_,
	weapons::reload_time const reload_time_
)
:
	weapon(
		env,
		type_,
		weapons::range(1000), // FIXME
		weapons::magazine_size(1),
		weapons::magazine_count(1),
		base_cooldown_,
		cast_point_,
		reload_time_
	),
	damage_(damage_),
	aoe_(aoe_)
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
				damage_,
				aoe_,
				a.dest()
			)
		)
	);
}
