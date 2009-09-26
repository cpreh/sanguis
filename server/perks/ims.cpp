#include "ims.hpp"
#include "../entities/property.hpp"
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
	dynamic_cast<
		entities::movable &
	>(
		entity_
	)
	.movement_speed().multiply_max(
		factor()
	);
}

bool
sanguis::server::perks::ims::can_raise_level() const
{
	return level() < 7;
}

sanguis::server::space_unit
sanguis::server::perks::ims::factor() const
{
	return
		static_cast<space_unit>(level())
		* static_cast<space_unit>(0.1);
}
