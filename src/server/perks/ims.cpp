#include <sanguis/perk_type.hpp>
#include <sanguis/server/entities/base.hpp>
#include <sanguis/server/entities/with_velocity.hpp>
#include <sanguis/server/entities/property/linear_change.hpp>
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
{
}

void
sanguis::server::perks::ims::change(
	sanguis::server::entities::base &_entity,
	sanguis::server::perks::level_diff const _diff
)
{
	sanguis::server::perks::change_simple<
		sanguis::server::entities::with_velocity
	>(
		&sanguis::server::entities::property::linear_change,
		_entity,
		&sanguis::server::entities::with_velocity::movement_speed,
		0.1f,
		_diff
	);
}
