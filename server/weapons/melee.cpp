#include "melee.hpp"
#include "delayed_attack.hpp"
#include "../entities/entity.hpp"
#include "../entities/entity_with_weapon.hpp"
#include "../entities/property.hpp"
#include "../entities/projectiles/melee.hpp"

sanguis::server::weapons::melee::melee(
	server::environment const &env,
	space_unit const range,
	time_type const base_cooldown,
	space_unit const damage)
:
	weapon(
		env,
		weapon_type::melee,
		range,
		unlimited_magazine,
		unlimited_magazine,
		base_cooldown,
		static_cast<time_type>(
			0),
		static_cast<time_type>(
			0)),
	damage(damage)
{}

void sanguis::server::weapons::melee::do_attack(
	delayed_attack const &a)
{
	insert(
		entities::auto_ptr(
			new entities::projectiles::melee(
				environment(),
				a.dest(),
				a.team(),
				damage)));
}

void sanguis::server::weapons::melee::on_init_attack(
	entities::entity_with_weapon &owner)
{
	owner.property(
		entities::property_type::movement_speed
	).restrict(
		static_cast<space_unit>(0)
	);
}

void sanguis::server::weapons::melee::on_castpoint(
	entities::entity_with_weapon &owner)
{
	owner.property(
		entities::property_type::movement_speed)
			.unrestrict();
}
