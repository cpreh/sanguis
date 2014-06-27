#include <sanguis/server/damage/type_fwd.hpp>
#include <sanguis/server/entities/with_perks.hpp>
#include <sanguis/server/entities/with_weapon.hpp>
#include <sanguis/server/entities/property/constant_change.hpp>
#include <sanguis/server/perks/change_factor.hpp>
#include <sanguis/server/perks/change_simple.hpp>
#include <sanguis/server/perks/constant_damage_change.hpp>
#include <sanguis/server/perks/level_diff.hpp>
#include <fcppt/config/external_begin.hpp>
#include <functional>
#include <fcppt/config/external_end.hpp>


void
sanguis::server::perks::constant_damage_change(
	sanguis::server::entities::with_perks &_entity,
	sanguis::server::damage::type const _type,
	sanguis::server::perks::level_diff const _diff,
	sanguis::server::perks::change_factor const _factor
)
{
	sanguis::server::perks::change_simple<
		sanguis::server::entities::with_weapon
	>(
		&sanguis::server::entities::property::constant_change,
		_entity,
		std::bind(
			&sanguis::server::entities::with_weapon::extra_damage,
			std::placeholders::_1,
			_type
		),
		_factor,
		_diff
	);
}
