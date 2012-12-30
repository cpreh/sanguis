#include <sanguis/diff_clock_fwd.hpp>
#include <sanguis/duration_second.hpp>
#include <sanguis/weapon_type.hpp>
#include <sanguis/server/center.hpp>
#include <sanguis/server/entities/base.hpp>
#include <sanguis/server/entities/insert_parameters_center.hpp>
#include <sanguis/server/entities/with_velocity.hpp>
#include <sanguis/server/entities/with_weapon.hpp>
#include <sanguis/server/entities/projectiles/melee.hpp>
#include <sanguis/server/environment/object.hpp>
#include <sanguis/server/weapons/base_cooldown.hpp>
#include <sanguis/server/weapons/cast_point.hpp>
#include <sanguis/server/weapons/damage.hpp>
#include <sanguis/server/weapons/delayed_attack.hpp>
#include <sanguis/server/weapons/melee.hpp>
#include <sanguis/server/weapons/range.hpp>
#include <sanguis/server/weapons/reload_time.hpp>
#include <sanguis/server/weapons/unlimited_magazine_size.hpp>
#include <sanguis/server/weapons/unlimited_magazine_count.hpp>
#include <sanguis/server/weapons/weapon.hpp>
#include <fcppt/make_unique_ptr.hpp>


sanguis::server::weapons::melee::melee(
	sanguis::diff_clock const &_diff_clock,
	sanguis::server::weapons::range const _range,
	sanguis::server::weapons::base_cooldown const _base_cooldown,
	sanguis::server::weapons::damage const _damage
)
:
	sanguis::server::weapons::weapon(
		_diff_clock,
		sanguis::weapon_type::melee,
		_range,
		sanguis::server::weapons::unlimited_magazine_size,
		sanguis::server::weapons::unlimited_magazine_count,
		_base_cooldown,
		sanguis::server::weapons::cast_point(
			sanguis::duration_second(
				0.f
			)
		),
		sanguis::server::weapons::reload_time(
			sanguis::duration_second(
				0.f
			)
		)
	),
	damage_(
		_damage
	)
{
}

sanguis::server::weapons::melee::~melee()
{
}

void
sanguis::server::weapons::melee::do_attack(
	sanguis::server::weapons::delayed_attack const &_attack
)
{
	_attack.environment().insert(
		fcppt::make_unique_ptr<
			sanguis::server::entities::projectiles::melee
		>(
			this->diff_clock(),
			_attack.team(),
			damage_
		),
		sanguis::server::entities::insert_parameters_center(
			sanguis::server::center(
				_attack.dest()
			)
		)
	);
}

void
sanguis::server::weapons::melee::on_init_attack(
	sanguis::server::entities::with_weapon &_owner
)
{
	sanguis::server::entities::with_velocity *const movable(
		dynamic_cast<
			sanguis::server::entities::with_velocity *
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
	sanguis::server::entities::with_weapon &_owner
)
{
	sanguis::server::entities::with_velocity *const movable(
		dynamic_cast<
			sanguis::server::entities::with_velocity *
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
