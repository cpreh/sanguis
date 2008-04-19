#include "melee.hpp"
#include "../collision.hpp"
#include "../entity.hpp"

sanguis::server::weapons::melee::melee(
	const messages::space_unit range,
	const time_type base_cooldown,
	const messages::space_unit damage)
: weapon(
	range,
	base_cooldown),
  damage(damage)
{}

void sanguis::server::weapons::melee::do_attack(
	entity const &from,
	messages::pos_type const& to)
{
	// TODO: spawn melee bullet here
}
