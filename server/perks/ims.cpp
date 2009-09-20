#include "ims.hpp"
#include "../entities/property.hpp"
#include "../entities/entity.hpp"

sanguis::server::perks::ims::ims()
:
	perk(
		perk_type::ims
	)
{}

void sanguis::server::perks::ims::do_apply(
	entities::entity &e,
	time_type,
	environment::object_ptr,
	environment::load_context_ptr
)
{
	e.property(
		entities::property_type::movement_speed)
		.multiply_max(factor());
}

bool sanguis::server::perks::ims::can_raise_level() const
{
	return level() < 7;
}

sanguis::server::space_unit
sanguis::server::perks::ims::factor() const
{
	return static_cast<space_unit>(level())
		* static_cast<space_unit>(0.1);
}
