#include "health.hpp"
#include "../entities/property.hpp"
#include "../entities/with_health.hpp"

sanguis::server::perks::health::health()
:
	perk(
		perk_type::health
	)
{}

void
sanguis::server::perks::health::do_apply(
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
	.health().add_to_max(
		static_cast<space_unit>(level())
		* static_cast<space_unit>(20)
	);
}

bool
sanguis::server::perks::health::can_raise_level() const
{
	return level() < 10;
}
