#include "pistol.hpp"
#include "../entity.hpp"
#include "../projectiles/simple_bullet.hpp"

sanguis::server::weapons::pistol::pistol(
	const time_type base_cooldown,
	const insert_callback insert)
: weapon(
	1000, // FIXME
	base_cooldown,
	insert)
{}

void sanguis::server::weapons::pistol::do_attack(
	entity const &from,
	messages::pos_type const &to)
{
	insert(
		entity_ptr(
			new projectiles::simple_bullet(
				from.center(),
				from.angle(),
				from.team(),
				messages::mu(5))));
}
