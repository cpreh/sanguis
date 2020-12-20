#include <sanguis/perk_type.hpp>
#include <sanguis/server/damage/type.hpp>
#include <sanguis/server/entities/with_perks_fwd.hpp>
#include <sanguis/server/perks/change_factor.hpp>
#include <sanguis/server/perks/constant_damage_change.hpp>
#include <sanguis/server/perks/level_diff.hpp>
#include <sanguis/server/perks/piercing_damage.hpp>


sanguis::server::perks::piercing_damage::piercing_damage()
:
	sanguis::server::perks::perk(
		sanguis::perk_type::piercing_damage
	)
{
}

sanguis::server::perks::piercing_damage::~piercing_damage()
= default;

void
sanguis::server::perks::piercing_damage::change(
	sanguis::server::entities::with_perks &_entity,
	sanguis::server::perks::level_diff const _diff
)
{
	sanguis::server::perks::constant_damage_change(
		_entity,
		sanguis::server::damage::type::piercing,
		_diff,
		sanguis::server::perks::change_factor(
			0.2F // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
		)
	);
}
