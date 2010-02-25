#include "irs.hpp"
#include "../entities/property/value.hpp"
#include "../entities/property/linear_add.hpp"
#include "../entities/property/linear_remove.hpp"
#include "../entities/with_weapon.hpp"

sanguis::server::perks::irs::irs()
:
	perk(
		perk_type::irs
	)
{}

void
sanguis::server::perks::irs::apply(
	entities::base &entity_
)
{
	entities::property::linear_add(
		dynamic_cast<
			entities::with_weapon &
		>(
			entity_
		)
		.reload_speed(),
		factor()
	);
}

void
sanguis::server::perks::irs::unapply(
	entities::base &entity_
)
{
	entities::property::linear_remove(
		dynamic_cast<
			entities::with_weapon &
		>(
			entity_
		)
		.reload_speed(),
		factor()
	);
}

bool
sanguis::server::perks::irs::can_raise_level() const
{
	return level() < 4;
}

sanguis::server::entities::property::value const
sanguis::server::perks::irs::factor() const
{
	return
		entities::property::value(
			level(),
			2
		);
}
