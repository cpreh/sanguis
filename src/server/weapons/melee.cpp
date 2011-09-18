#include <sanguis/server/weapons/melee.hpp>
#include <sanguis/server/weapons/delayed_attack.hpp>
#include <sanguis/server/weapons/unlimited_magazine_size.hpp>
#include <sanguis/server/weapons/unlimited_magazine_count.hpp>
#include <sanguis/server/environment/object.hpp>
#include <sanguis/server/entities/insert_parameters_center.hpp>
#include <sanguis/server/entities/base.hpp>
#include <sanguis/server/entities/with_weapon.hpp>
#include <sanguis/server/entities/with_velocity.hpp>
#include <sanguis/server/entities/projectiles/melee.hpp>
#include <fcppt/cref.hpp>
#include <fcppt/make_unique_ptr.hpp>

sanguis::server::weapons::melee::melee(
	sanguis::diff_clock const &_diff_clock,
	weapons::range const _range,
	weapons::base_cooldown const _base_cooldown,
	weapons::damage const _damage
)
:
	weapon(
		_diff_clock,
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
				fcppt::cref(
					this->diff_clock()
				),
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
