#include "ims.hpp"
#include "../entities/property/value.hpp"
#include "../entities/property/linear_add.hpp"
#include "../entities/property/linear_remove.hpp"
#include "../entities/movable.hpp"

sanguis::server::perks::ims::ims()
:
	perk(
		perk_type::ims
	)
{}

void
sanguis::server::perks::ims::apply(
	entities::base &entity_
)
{
	entities::property::linear_add(
		dynamic_cast<
			entities::movable &
		>(
			entity_
		)
		.movement_speed(),
		factor()
	);
}

void
sanguis::server::perks::ims::unapply(
	entities::base &entity_
)
{
	entities::property::linear_remove(
		dynamic_cast<
			entities::movable &
		>(
			entity_
		)
		.movement_speed(),
		factor()
	);
}

bool
sanguis::server::perks::ims::can_raise_level() const
{
	return level() < 7;
}

sanguis::server::entities::property::value const
sanguis::server::perks::ims::factor() const
{
	return
		entities::property::value(
			level(),
			10
		);
}
