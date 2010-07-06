#include "ims.hpp"
#include "change_simple.hpp"
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
	perks::change_simple<
		entities::movable
	>(
		&entities::property::linear_change,
		entity_,
		&entities::movable::movement_speed,
		0.1f,
		diff_
	);
}

sanguis::server::perks::level_type
sanguis::server::perks::ims::max_level() const
{
	return 7;
}
