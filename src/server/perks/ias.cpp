#include "ias.hpp"
#include "change_simple.hpp"
#include "../entities/property/linear_change.hpp"
#include "../entities/with_weapon.hpp"

sanguis::server::perks::ias::ias()
:
	perk(
		perk_type::ias
	)
{
}

sanguis::server::perks::ias::~ias()
{
}

void
sanguis::server::perks::ias::change(
	entities::base &_entity,
	level_diff const _diff
)
{
	perks::change_simple<
		entities::with_weapon
	>(
		&entities::property::linear_change,
		_entity,
		&entities::with_weapon::attack_speed,
		0.2f,
		_diff
	);
}

sanguis::server::level const
sanguis::server::perks::ias::max_level() const
{
	return
		server::level(
			8
		);
}
