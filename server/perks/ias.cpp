#include "ias.hpp"
#include "../entities/property/value.hpp"
#include "../entities/property/linear_add.hpp"
#include "../entities/property/linear_remove.hpp"
#include "../entities/with_weapon.hpp"

sanguis::server::perks::ias::ias()
:
	perk(
		perk_type::ias
	)
{}

void
sanguis::server::perks::ias::apply(
	entities::base &entity_
)
{
	entities::property::linear_add(
		dynamic_cast<
			entities::with_weapon &
		>(
			entity_
		)
		.attack_speed(),
		factor()
	);
}

void
sanguis::server::perks::ias::unapply(
	entities::base &entity_
)
{
	entities::property::linear_remove(
		dynamic_cast<
			entities::with_weapon &
		>(
			entity_
		)
		.attack_speed(),
		factor()
	);
}

bool
sanguis::server::perks::ias::can_raise_level() const
{
	return level() <= 8;
}

sanguis::server::entities::property::value const
sanguis::server::perks::ias::factor() const
{
	return
		entities::property::value(
			level(),
			5
		);
}
