#include "ims.hpp"
#include "../entities/property/value.hpp"
#include "../entities/property/linear_add.hpp"
#include "../entities/movable.hpp"

sanguis::server::perks::ims::ims()
:
	perk(
		perk_type::ims
	)
{}

void
sanguis::server::perks::ims::do_apply(
	entities::base &entity_,
	time_type,
	environment::object_ptr
)
{
	entities::property::linear_add(
		dynamic_cast<
			entities::movable &
		>(
			entity_
		)
		.movement_speed(),
		entities::property::value(
			level(),
			10
		)
	);
}

bool
sanguis::server::perks::ims::can_raise_level() const
{
	return level() < 7;
}
