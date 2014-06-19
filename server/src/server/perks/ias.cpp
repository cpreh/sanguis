#include <sanguis/perk_type.hpp>
#include <sanguis/server/entities/with_perks.hpp>
#include <sanguis/server/entities/with_weapon.hpp>
#include <sanguis/server/entities/property/linear_change.hpp>
#include <sanguis/server/perks/change_factor.hpp>
#include <sanguis/server/perks/change_simple.hpp>
#include <sanguis/server/perks/ias.hpp>
#include <sanguis/server/perks/level_diff.hpp>
#include <fcppt/config/external_begin.hpp>
#include <functional>
#include <fcppt/config/external_end.hpp>


sanguis::server::perks::ias::ias()
:
	sanguis::server::perks::perk(
		sanguis::perk_type::ias
	)
{
}

sanguis::server::perks::ias::~ias()
{
}

void
sanguis::server::perks::ias::change(
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
			&sanguis::server::entities::with_weapon::attack_speed,
			std::placeholders::_1
		),
		sanguis::server::perks::change_factor(
			0.2f
		),
		_diff
	);
}
