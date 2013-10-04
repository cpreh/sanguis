#include <sanguis/diff_clock_fwd.hpp>
#include <sanguis/duration_second.hpp>
#include <sanguis/primary_weapon_type.hpp>
#include <sanguis/string_vector.hpp>
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
#include <sanguis/server/weapons/make_attribute.hpp>
#include <sanguis/server/weapons/melee.hpp>
#include <sanguis/server/weapons/optional_magazine_size.hpp>
#include <sanguis/server/weapons/optional_reload_time.hpp>
#include <sanguis/server/weapons/range.hpp>
#include <sanguis/server/weapons/weapon.hpp>
#include <fcppt/insert_to_fcppt_string.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/text.hpp>


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
		sanguis::server::weapons::optional_magazine_size(),
		_base_cooldown,
		sanguis::server::weapons::cast_point(
			sanguis::duration_second(
				0.f
			)
		),
		sanguis::server::weapons::optional_reload_time()
	),
	damage_(
		_damage
	)
{
}

sanguis::server::weapons::melee::~melee()
{
}

bool
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

	return
		true;
}

sanguis::string_vector
sanguis::server::weapons::melee::attributes() const
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
