#include <sanguis/diff_clock_fwd.hpp>
#include <sanguis/string_vector.hpp>
#include <sanguis/weapon_type.hpp>
#include <sanguis/server/weapons/base_cooldown.hpp>
#include <sanguis/server/weapons/cast_point.hpp>
#include <sanguis/server/weapons/damage.hpp>
#include <sanguis/server/weapons/delayed_attack.hpp>
#include <sanguis/server/weapons/magazine_size.hpp>
#include <sanguis/server/weapons/make_attribute.hpp>
#include <sanguis/server/weapons/pistol.hpp>
#include <sanguis/server/weapons/range.hpp>
#include <sanguis/server/weapons/reload_time.hpp>
#include <sanguis/server/weapons/unlimited_magazine_count.hpp>
#include <sanguis/server/weapons/weapon.hpp>
#include <sanguis/server/entities/base.hpp>
#include <sanguis/server/entities/insert_parameters.hpp>
#include <sanguis/server/entities/projectiles/simple_bullet.hpp>
#include <sanguis/server/environment/insert_no_result.hpp>
#include <sanguis/server/environment/object.hpp>
#include <fcppt/insert_to_fcppt_string.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/text.hpp>


sanguis::server::weapons::pistol::pistol(
	sanguis::diff_clock const &_diff_clock,
	sanguis::weapon_type const _type,
	sanguis::server::weapons::base_cooldown const _base_cooldown,
	sanguis::server::weapons::damage const _damage,
	sanguis::server::weapons::cast_point const _cast_point,
	sanguis::server::weapons::magazine_size const _magazine_size,
	sanguis::server::weapons::reload_time const _reload_time,
	sanguis::server::weapons::range const _range
)
:
	sanguis::server::weapons::weapon(
		_diff_clock,
		_type,
		_range,
		_magazine_size,
		sanguis::server::weapons::unlimited_magazine_count,
		_base_cooldown,
		_cast_point,
		_reload_time
	),
	damage_(
		_damage
	)
{
}

sanguis::server::weapons::pistol::~pistol()
{
}

void
sanguis::server::weapons::pistol::do_attack(
	sanguis::server::weapons::delayed_attack const &_attack
)
{
	sanguis::server::environment::insert_no_result(
		_attack.environment(),
		fcppt::make_unique_ptr<
			sanguis::server::entities::projectiles::simple_bullet
		>(
			this->diff_clock(),
			_attack.environment().load_context(),
			_attack.team(),
			damage_,
			sanguis::server::direction(
				_attack.angle().get()
			)
		),
		sanguis::server::entities::insert_parameters(
			_attack.spawn_point(),
			_attack.angle()
		)
	);
}

sanguis::string_vector
sanguis::server::weapons::pistol::attributes() const
{
	return
		sanguis::string_vector{
			sanguis::server::weapons::make_attribute(
				FCPPT_TEXT("damage"),
				fcppt::insert_to_fcppt_string(
					damage_
				)
			)
		};
}
