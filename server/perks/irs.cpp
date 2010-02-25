#include "irs.hpp"
#include "diff_factor.hpp"
#include "../entities/property/value.hpp"
#include "../entities/property/linear_change.hpp"
#include "../entities/with_weapon.hpp"

sanguis::server::perks::irs::irs()
:
	perk(
		perk_type::irs
	)
{}

void
sanguis::server::perks::irs::change(
	entities::base &entity_,
	level_diff const diff_
)
{
	entities::property::linear_change(
		dynamic_cast<
			entities::with_weapon &
		>(
			entity_
		)
		.reload_speed(),
		diff_factor(
			factor,
			level(),
			diff_
		)
	);
}

bool
sanguis::server::perks::irs::can_raise_level() const
{
	return level() < 4;
}

sanguis::server::entities::property::value const
sanguis::server::perks::irs::factor(
	level_type const level_
)
{
	return
		entities::property::value(
			level_,
			2
		);
}
