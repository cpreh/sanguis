#include "melee.hpp"
#include "../damage_types.hpp"
#include "../entity.hpp"
#include "../projectiles/melee.hpp"

sanguis::server::weapons::melee::melee(
	const environment &env,
	const weapon_type::type type_,
	const messages::space_unit range,
	const time_type base_cooldown,
	const messages::space_unit damage)
: weapon(
		env,
		type_,
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
				get_environment(),
				(damage::normal=messages::mu(0.5)),
				to,
				from.team(),
				damage)));
}
