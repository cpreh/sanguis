#include "melee.hpp"
#include "../damage_types.hpp"
#include "../entities/entity.hpp"
#include "../entities/projectiles/melee.hpp"
#include <sge/iostream.hpp>

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
	entities::entity const &from,
	messages::pos_type const& to)
{
	sge::cerr << "server: in weapons::melee::do_attack, inserting melee projectile\n";
	insert(
		entities::auto_ptr(
			new entities::projectiles::melee(
				get_environment(),
				damage::list(messages::mu(0)),
				to,
				from.team(),
				damage)));
}
