#include "ims.hpp"
#include "diff_factor.hpp"
#include "../entities/property/value.hpp"
#include "../entities/property/linear_change.hpp"
#include "../entities/movable.hpp"

sanguis::server::perks::ims::ims()
:
	perk(
		perk_type::ims
	)
{}

void
sanguis::server::perks::ims::change(
	entities::base &entity_,
	level_diff const diff_
)
{
	entities::property::linear_change(
		dynamic_cast<
			entities::movable &
		>(
			entity_
		)
		.movement_speed(),
		diff_factor(
			factor,
			level(),
			diff_
		)
	);
}

bool
sanguis::server::perks::ims::can_raise_level() const
{
	return level() < 7;
}

sanguis::server::entities::property::value
sanguis::server::perks::ims::factor(
	level_type const level_
)
{
	return level_ * 0.1f;
}
