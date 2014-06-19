#include <sanguis/perk_type.hpp>
#include <sanguis/server/entities/with_health.hpp>
#include <sanguis/server/entities/with_perks.hpp>
#include <sanguis/server/entities/property/constant_change.hpp>
#include <sanguis/server/perks/change_factor.hpp>
#include <sanguis/server/perks/change_simple.hpp>
#include <sanguis/server/perks/health.hpp>
#include <sanguis/server/perks/level_diff.hpp>
#include <fcppt/config/external_begin.hpp>
#include <functional>
#include <fcppt/config/external_end.hpp>


sanguis::server::perks::health::health()
:
	sanguis::server::perks::perk(
		sanguis::perk_type::health
	)
{
}

sanguis::server::perks::health::~health()
{
}

void
sanguis::server::perks::health::change(
	sanguis::server::entities::with_perks &_entity,
	sanguis::server::perks::level_diff const _diff
)
{
	sanguis::server::perks::change_simple<
		sanguis::server::entities::with_health
	>(
		&sanguis::server::entities::property::constant_change,
		_entity,
		std::bind(
			&sanguis::server::entities::with_health::health,
			std::placeholders::_1
		),
		sanguis::server::perks::change_factor(
			20.f
		),
		_diff
	);
}
