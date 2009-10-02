#include "regeneration.hpp"
#include "../entities/property/value.hpp"
#include "../entities/property/constant_add.hpp"
#include "../entities/property/constant_remove.hpp"
#include "../entities/with_health.hpp"

sanguis::server::perks::regeneration::regeneration()
:
	perk(
		perk_type::regeneration
	)
{}

void
sanguis::server::perks::regeneration::apply(
	entities::base &entity_
)
{
	entities::property::constant_add(
		dynamic_cast<
			entities::with_health &
		>(
			entity_
		)
		.regeneration(),
		factor()
	);
}

void
sanguis::server::perks::regeneration::unapply(
	entities::base &entity_
)
{
	entities::property::constant_remove(
		dynamic_cast<
			entities::with_health &
		>(
			entity_
		)
		.regeneration(),
		factor()
	);
}

bool
sanguis::server::perks::regeneration::can_raise_level() const
{
	return level() < 3;
}

sanguis::server::entities::property::value const
sanguis::server::perks::regeneration::factor() const
{
	return
		entities::property::value(
			level() * 3,
			4
		);
}
