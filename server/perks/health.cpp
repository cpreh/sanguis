#include "health.hpp"
#include "../entities/property/object.hpp"
#include "../entities/property/value.hpp"
#include "../entities/property/constant_add.hpp"
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
	entities::property::constant_add(
		dynamic_cast<
			entities::with_health &
		>(
			entity_
		)
		.health(),
		entities::property::value(
			level() * 20,
			1
		)
	);
}

bool
sanguis::server::perks::health::can_raise_level() const
{
	return level() < 10;
}
