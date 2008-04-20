#include "melee.hpp"
#include "../entity.hpp"
#include "../projectiles/melee.hpp"

sanguis::server::weapons::melee::melee(
	const messages::space_unit range,
	const time_type base_cooldown,
	const insert_callback insert,
	const messages::space_unit damage)
: weapon(
		range,
		base_cooldown,
		insert),
  damage(damage)
{}

void sanguis::server::weapons::melee::do_attack(
	entity const &from,
	messages::pos_type const& to)
{
	insert(
		entity_ptr(
			new projectiles::melee(
				to,
				from.team(),
				damage)));
}
