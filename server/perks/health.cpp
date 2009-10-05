#include "health.hpp"
#include "../entities/property/value.hpp"
#include "../entities/property/constant_add.hpp"
#include "../entities/property/constant_remove.hpp"
#include "../entities/with_health.hpp"

sanguis::server::perks::health::health()
:
	perk(
		perk_type::health
	)
{}

void
sanguis::server::perks::health::apply(
	entities::base &entity_
)
{
	entities::property::constant_add(
		dynamic_cast<
			entities::with_health &
		>(
			entity_
		)
		.health(),
		factor()
	);
}

void
sanguis::server::perks::health::unapply(
	entities::base &entity_
)
{
	entities::property::constant_remove(
		dynamic_cast<
			entities::with_health &
		>(
			entity_
		)
		.health(),
		factor()
	);
}

bool
sanguis::server::perks::health::can_raise_level() const
{
	return level() <= 10;
}

sanguis::server::entities::property::value const
sanguis::server::perks::health::factor() const
{
	return
		entities::property::value(
			level() * 20,
			1
		);
}
