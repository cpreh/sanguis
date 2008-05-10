#include "pistol.hpp"
#include "../damage_types.hpp"
#include "../entities/entity.hpp"
#include "../entities/projectiles/simple_bullet.hpp"

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
	entities::entity const &from,
	messages::pos_type const &to)
{
	insert(
		entities::entity_ptr(
			new entities::projectiles::simple_bullet(
				get_environment(),
				(damage::normal=messages::mu(1)),
				from.center(),
				from.angle(),
				from.team(),
				messages::mu(1))));
}
