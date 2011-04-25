#include "melee.hpp"
#include "delayed_attack.hpp"
#include "unlimited_magazine_size.hpp"
#include "unlimited_magazine_count.hpp"
#include "../environment/object.hpp"
#include "../entities/insert_parameters_center.hpp"
#include "../entities/base.hpp"
#include "../entities/with_weapon.hpp"
#include "../entities/with_velocity.hpp"
#include "../entities/projectiles/melee.hpp"
#include <fcppt/make_unique_ptr.hpp>

sanguis::server::weapons::melee::melee(
	weapons::range const _range,
	weapons::base_cooldown const _base_cooldown,
	weapons::damage const _damage
)
:
	weapon(
		weapon_type::melee,
		_range,
		unlimited_magazine_size,
		unlimited_magazine_count,
		_base_cooldown,
		weapons::cast_point(
			0.f
		),
		weapons::reload_time(
			0.f
		)
	),
	damage_(_damage)
{
}

sanguis::server::weapons::melee::~melee()
{
}

void
sanguis::server::weapons::melee::do_attack(
	delayed_attack const &_attack
)
{
	_attack.environment().insert(
		entities::unique_ptr(
			fcppt::make_unique_ptr<
				entities::projectiles::melee
			>(
				_attack.team(),
				damage_
			)
		),
		entities::insert_parameters_center(
			server::center(
				_attack.dest()
			)
		)
	);
}

void
sanguis::server::weapons::melee::on_init_attack(
	entities::with_weapon &_owner
)
{
	entities::with_velocity *const movable(
		dynamic_cast<
			entities::with_velocity *
		>(
			&_owner
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
	entities::with_weapon &_owner
)
{
	entities::with_velocity *const movable(
		dynamic_cast<
			entities::with_velocity *
		>(
			&_owner
		)
	);

#if 0
	if(
		movable_
	)
		movable_->movement_speed().unrestrict();
#endif
}
