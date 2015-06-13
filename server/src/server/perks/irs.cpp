#include <sanguis/perk_type.hpp>
#include <sanguis/server/entities/with_perks.hpp>
#include <sanguis/server/entities/property/always_max.hpp>
#include <sanguis/server/entities/property/linear_change.hpp>
#include <sanguis/server/perks/change_factor.hpp>
#include <sanguis/server/perks/change_simple.hpp>
#include <sanguis/server/perks/irs.hpp>
#include <sanguis/server/perks/level_diff.hpp>


sanguis::server::perks::irs::irs()
:
	sanguis::server::perks::perk(
		sanguis::perk_type::irs
	)
{
}

sanguis::server::perks::irs::~irs()
{
}

void
sanguis::server::perks::irs::change(
	sanguis::server::entities::with_perks &_entity,
	sanguis::server::perks::level_diff const _diff
)
{
	sanguis::server::perks::change_simple(
		&sanguis::server::entities::property::linear_change,
		_entity.reload_speed(),
		sanguis::server::perks::change_factor(
			0.5f
		),
		_diff
	);
}
