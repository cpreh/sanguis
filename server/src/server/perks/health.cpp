#include <sanguis/perk_type.hpp>
#include <sanguis/server/entities/with_perks.hpp>
#include <sanguis/server/entities/property/changeable.hpp>
#include <sanguis/server/entities/property/constant_change.hpp>
#include <sanguis/server/perks/change_factor.hpp>
#include <sanguis/server/perks/change_simple.hpp>
#include <sanguis/server/perks/health.hpp>
#include <sanguis/server/perks/level_diff.hpp>


sanguis::server::perks::health::health()
:
	sanguis::server::perks::perk(
		sanguis::perk_type::health
	)
{
}

sanguis::server::perks::health::~health()
= default;

void
sanguis::server::perks::health::change(
	sanguis::server::entities::with_perks &_entity,
	sanguis::server::perks::level_diff const _diff
)
{
	sanguis::server::perks::change_simple(
		&sanguis::server::entities::property::constant_change,
		_entity.health(),
		sanguis::server::perks::change_factor(
			20.F // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
		),
		_diff
	);
}
