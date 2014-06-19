#include <sanguis/perk_type.hpp>
#include <sanguis/server/entities/with_perks.hpp>
#include <sanguis/server/entities/with_velocity.hpp>
#include <sanguis/server/entities/property/linear_change.hpp>
#include <sanguis/server/perks/change_factor.hpp>
#include <sanguis/server/perks/change_simple.hpp>
#include <sanguis/server/perks/ims.hpp>
#include <sanguis/server/perks/level_diff.hpp>
#include <fcppt/config/external_begin.hpp>
#include <functional>
#include <fcppt/config/external_end.hpp>


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
	sanguis::server::entities::with_perks &_entity,
	sanguis::server::perks::level_diff const _diff
)
{
	sanguis::server::perks::change_simple<
		sanguis::server::entities::with_velocity
	>(
		&sanguis::server::entities::property::linear_change,
		_entity,
		std::bind(
			&sanguis::server::entities::with_velocity::movement_speed,
			std::placeholders::_1
		),
		sanguis::server::perks::change_factor(
			0.1f
		),
		_diff
	);
}
