#include "pistol.hpp"
#include "delayed_attack.hpp"
#include "../damage_types.hpp"
#include "../entities/entity.hpp"
#include "../entities/projectiles/simple_bullet.hpp"

sanguis::server::weapons::pistol::pistol(
	environment const &env,
	weapon_type::type const type_,
	time_type const base_cooldown,
	messages::space_unit const damage,
	time_type const cast_point)
: weapon(
	env,
	type_,
	1000, // FIXME
	base_cooldown,
	cast_point),
  damage(damage)
{}

void sanguis::server::weapons::pistol::do_attack(
	delayed_attack const &a)
{
	insert(
		entities::auto_ptr(
			new entities::projectiles::simple_bullet(
				get_environment(),
				damage::list(messages::mu(0)),
				a.spawn_point(),
				a.angle(),
				a.team(),
				damage)));
}
