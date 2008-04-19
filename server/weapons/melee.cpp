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

bool sanguis::server::weapons::melee::attack(
	entity const &from, messages::pos_type const& to)
{
//	if(in_range(from, to, range()))
	{
		//to.attack(damage);
		return true;
	}
	return false;
}
