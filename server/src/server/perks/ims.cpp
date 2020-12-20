#include <sanguis/perk_type.hpp>
#include <sanguis/server/entities/with_perks.hpp>
#include <sanguis/server/entities/property/changeable.hpp>
#include <sanguis/server/entities/property/linear_change.hpp>
#include <sanguis/server/perks/change_factor.hpp>
#include <sanguis/server/perks/change_simple.hpp>
#include <sanguis/server/perks/ims.hpp>
#include <sanguis/server/perks/level_diff.hpp>


sanguis::server::perks::ims::ims()
:
	sanguis::server::perks::perk(
		sanguis::perk_type::ims
	)
{
}

sanguis::server::perks::ims::~ims()
= default;

void
sanguis::server::perks::ims::change(
	sanguis::server::entities::with_perks &_entity,
	sanguis::server::perks::level_diff const _diff
)
{
	sanguis::server::perks::change_simple(
		&sanguis::server::entities::property::linear_change,
		_entity.movement_speed(),
		sanguis::server::perks::change_factor(
			0.1F // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
		),
		_diff
	);
}
