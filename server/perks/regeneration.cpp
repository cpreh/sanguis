#include "regeneration.hpp"
#include "../entities/property.hpp"
#include "../entities/entity.hpp"

sanguis::server::perks::regeneration::regeneration()
:
	perk(
		perk_type::regeneration
	)
{}

void sanguis::server::perks::regeneration::do_apply(
	entities::entity &e,
	time_type,
	environment const &)
{
	e.property(
		entities::property_type::health_regeneration
	).add_to_max(
		static_cast<space_unit>(level()) * static_cast<space_unit>(.75)
	);
}

bool sanguis::server::perks::regeneration::can_raise_level() const
{
	return level() < 3;
}
