#include <sanguis/server/perks/ims.hpp>
#include <sanguis/server/perks/change_simple.hpp>
#include <sanguis/server/entities/property/linear_change.hpp>
#include <sanguis/server/entities/with_velocity.hpp>

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
		entities::with_velocity
	>(
		&entities::property::linear_change,
		_entity,
		&entities::with_velocity::movement_speed,
		0.1f,
		_diff
	);
}
