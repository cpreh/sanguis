#include "melee.hpp"
#include "delayed_attack.hpp"
#include "unlimited_magazine_size.hpp"
#include "unlimited_magazine_count.hpp"
#include "../environment/object.hpp"
#include "../entities/property/object.hpp"
#include "../entities/insert_parameters_pos.hpp"
#include "../entities/base.hpp"
#include "../entities/with_weapon.hpp"
#include "../entities/movable.hpp"
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
				a.team(),
				damage_
			)
		),
		entities::insert_parameters_pos(
			a.spawn_point()
		)
	);
}

void
sanguis::server::weapons::melee::on_init_attack(
	entities::with_weapon &owner_
)
{
	entities::movable *const movable_(
		dynamic_cast<
			entities::movable *
		>(
			&owner_
		)
	);

#if 0
	if(
		movable_
	)
		movable_->movement_speed().restrict(
			0
		);
#endif
}

void
sanguis::server::weapons::melee::on_castpoint(
	entities::with_weapon &owner_
)
{
	entities::movable *const movable_(
		dynamic_cast<
			entities::movable *
		>(
			&owner_
		)
	);

#if 0
	if(
		movable_
	)
		movable_->movement_speed().unrestrict();
#endif
}
