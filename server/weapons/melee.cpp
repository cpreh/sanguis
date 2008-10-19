#include "melee.hpp"
#include "delayed_attack.hpp"
#include "../entities/entity.hpp"
#include "../entities/entity_with_weapon.hpp"
#include "../entities/projectiles/melee.hpp"
#include "../../exception.hpp"
#include <sge/text.hpp>

sanguis::server::weapons::melee::melee(
	environment const &env,
	space_unit const range,
	time_type const base_cooldown,
	space_unit const damage)
:
	weapon(
		env,
		weapon_type::melee,
		range,
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
				get_environment(),
				a.dest(),
				a.team(),
				damage)));
}

void sanguis::server::weapons::melee::on_init_attack(
	entities::entity_with_weapon &owner)
{
	entities::property &speed(
		owner.get_property(
			entities::property::type::movement_speed));
	
	old_speed = speed.current();

	speed.current(
		messages::mu(0));
}

void sanguis::server::weapons::melee::on_castpoint(
	entities::entity_with_weapon &owner)
{
	if(!old_speed)
		throw exception(
			SGE_TEXT("old_speed not set in weapons::melee!"));
	owner.get_property(
		entities::property::type::movement_speed)
			.current(
				*old_speed);
	old_speed.reset();
}
