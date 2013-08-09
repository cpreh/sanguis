#include <sanguis/diff_clock_fwd.hpp>
#include <sanguis/duration_second.hpp>
#include <sanguis/primary_weapon_type.hpp>
#include <sanguis/weapon_type.hpp>
#include <sanguis/server/center.hpp>
#include <sanguis/server/entities/base.hpp>
#include <sanguis/server/entities/insert_parameters_center.hpp>
#include <sanguis/server/entities/projectiles/melee.hpp>
#include <sanguis/server/environment/insert_no_result.hpp>
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
		sanguis::weapon_type(
			sanguis::primary_weapon_type::melee
		),
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
	sanguis::server::environment::insert_no_result(
		_attack.environment(),
		fcppt::make_unique_ptr<
			sanguis::server::entities::projectiles::melee
		>(
			this->diff_clock(),
			_attack.team(),
			damage_
		),
		sanguis::server::entities::insert_parameters_center(
			sanguis::server::center(
				_attack.target().get()
			)
		)
	);
}
