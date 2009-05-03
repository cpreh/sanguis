#include "health.hpp"
#include "../entities/property.hpp"
#include "../entities/entity.hpp"

sanguis::server::perks::health::health()
:
	perk(
		perk_type::health
	)
{}

void sanguis::server::perks::health::do_apply(
	entities::entity &e,
	time_type,
	environment const &)
{
	e.property(
		entities::property_type::health)
		.add_to_max(
			level() * static_cast<space_unit>(20)
	);
}

bool sanguis::server::perks::health::can_raise_level() const
{
	return true;
}
