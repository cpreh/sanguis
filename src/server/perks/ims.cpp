#include "ims.hpp"
#include "change_simple.hpp"
#include "../entities/property/linear_change.hpp"
#include "../entities/movable.hpp"

sanguis::server::perks::ims::ims()
:
	perk(
		perk_type::ims
	)
{
}

sanguis::server::perks::ims::~ims()
{
}

void
sanguis::server::perks::ims::change(
	entities::base &_entity,
	level_diff const _diff
)
{
	perks::change_simple<
		entities::movable
	>(
		&entities::property::linear_change,
		_entity,
		&entities::movable::movement_speed,
		0.1f,
		_diff
	);
}

sanguis::server::level const
sanguis::server::perks::ims::max_level() const
{
	return
		server::level(
			7
		);
}
