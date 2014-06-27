#include <sanguis/perk_type.hpp>
#include <sanguis/server/damage/type.hpp>
#include <sanguis/server/entities/with_perks.hpp>
#include <sanguis/server/entities/with_weapon.hpp>
#include <sanguis/server/entities/property/linear_change.hpp>
#include <sanguis/server/perks/change_factor.hpp>
#include <sanguis/server/perks/change_simple.hpp>
#include <sanguis/server/perks/fire_damage.hpp>
#include <sanguis/server/perks/level_diff.hpp>
#include <fcppt/config/external_begin.hpp>
#include <functional>
#include <fcppt/config/external_end.hpp>


sanguis::server::perks::fire_damage::fire_damage()
:
	sanguis::server::perks::perk(
		sanguis::perk_type::fire_damage
	)
{
}

sanguis::server::perks::fire_damage::~fire_damage()
{
}

void
sanguis::server::perks::fire_damage::change(
	sanguis::server::entities::with_perks &_entity,
	sanguis::server::perks::level_diff const _diff
)
{
	sanguis::server::perks::change_simple<
		sanguis::server::entities::with_weapon
	>(
		&sanguis::server::entities::property::linear_change,
		_entity,
		std::bind(
			&sanguis::server::entities::with_weapon::extra_damage,
			std::placeholders::_1,
			sanguis::server::damage::type::fire
		),
		sanguis::server::perks::change_factor(
			0.2f
		),
		_diff
	);
}
