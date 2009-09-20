#include "melee.hpp"
#include "delayed_attack.hpp"
#include "unlimited_magazine_size.hpp"
#include "unlimited_magazine_count.hpp"
#include "../environment/object.hpp"
#include "../entities/insert_parameters.hpp"
#include "../entities/insert_parameters_pos.hpp"
#include "../entities/entity.hpp"
#include "../entities/entity_with_weapon.hpp"
#include "../entities/property.hpp"
#include "../entities/projectiles/melee.hpp"

sanguis::server::weapons::melee::melee(
	weapons::range const range_,
	weapons::base_cooldown const base_cooldown_,
	weapons::damage const damage_
)
:
	weapon(
		weapon_type::melee,
		range_,
		unlimited_magazine_size,
		unlimited_magazine_count,
		base_cooldown_,
		weapons::cast_point(
			0
		),
		weapons::reload_time(
			0
		)
	),
	damage_(damage_)
{}

void
sanguis::server::weapons::melee::do_attack(
	delayed_attack const &a
)
{
	a.environment()->insert(
		entities::auto_ptr(
			new entities::projectiles::melee(
				a.load_context(),
				a.team(),
				damage_
			)
		),
		entities::insert_parameters_pos(
			a.spawn_point()
		)
	);
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
		entities::property_type::movement_speed
	).unrestrict();
}
