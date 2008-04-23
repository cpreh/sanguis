#include "melee.hpp"
#include "../entity.hpp"
#include "../projectiles/melee.hpp"

sanguis::server::weapons::melee::melee(
	const send_callback &send_callback_,
	const insert_callback &insert_callback_,
	const messages::space_unit range,
	const time_type base_cooldown,
	const messages::space_unit damage)
: weapon(
		send_callback_,
		insert_callback_,
		range,
		base_cooldown),
  damage(damage)
{}

void sanguis::server::weapons::melee::do_attack(
	entity const &from,
	messages::pos_type const& to)
{
	insert(
		entity_ptr(
			new projectiles::melee(
				get_send_callback(),
				get_insert_callback(),
				to,
				from.team(),
				damage)));
}
