#include "melee.hpp"
#include "../collision.hpp"
#include "../entity.hpp"

sanguis::server::weapons::melee::melee(
	messages::space_unit range,
	time_type base_cooldown,
	insert_callback insert,
	messages::space_unit damage)
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
	// TODO: spawn melee bullet here
}
