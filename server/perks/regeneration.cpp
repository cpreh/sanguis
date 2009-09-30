#include "regeneration.hpp"
#include "../entities/property/object.hpp"
#include "../entities/property/value.hpp"
#include "../entities/property/constant_add.hpp"
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
	entities::property::constant_add(
		dynamic_cast<
			entities::with_health &
		>(
			entity_
		)
		.regeneration(),
		entities::property::value(
			level() * 3,
			4
		)
	);
}

bool
sanguis::server::perks::regeneration::can_raise_level() const
{
	return level() < 3;
}
