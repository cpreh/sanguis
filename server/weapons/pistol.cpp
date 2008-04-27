#include "pistol.hpp"
#include "../entity.hpp"
#include "../projectiles/simple_bullet.hpp"

sanguis::server::weapons::pistol::pistol(
	const environment &env,
	const weapon_type::type type_,
	const time_type base_cooldown)
: weapon(
	env,
	type_,
	1000, // FIXME
	base_cooldown)
{}

void sanguis::server::weapons::pistol::do_attack(
	entity const &from,
	messages::pos_type const &to)
{
	insert(
		entity_ptr(
			new projectiles::simple_bullet(
				get_environment(),
				from.center(),
				from.angle(),
				from.team(),
				messages::mu(1))));
}
