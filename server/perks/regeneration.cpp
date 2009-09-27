#include "regeneration.hpp"
#include "../entities/property.hpp"
#include "../entities/with_health.hpp"

sanguis::server::perks::regeneration::regeneration()
:
	perk(
		perk_type::regeneration
	)
{}

void
sanguis::server::perks::regeneration::do_apply(
	entities::base &entity_,
	time_type,
	environment::object_ptr
)
{
	dynamic_cast<
		entities::with_health &
	>(
		entity_
	)
	.regeneration().add_to_max(
		static_cast<space_unit>(level())
		* static_cast<space_unit>(.75)
	);
}

bool
sanguis::server::perks::regeneration::can_raise_level() const
{
	return level() < 3;
}
