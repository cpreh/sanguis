#include "irs.hpp"
#include "../entities/property.hpp"
#include "../entities/entity.hpp"

sanguis::server::perks::irs::irs()
:
	perk(
		perk_type::irs
	)
{}

void sanguis::server::perks::irs::do_apply(
	entities::entity &e,
	time_type,
	environment::object_ptr
)
{
	e.property(
		entities::property_type::reload_speed)
		.multiply_max(factor());
}

bool sanguis::server::perks::irs::can_raise_level() const
{
	return level() < 4;
}

sanguis::server::space_unit
sanguis::server::perks::irs::factor() const
{
	return static_cast<space_unit>(level())
		* static_cast<space_unit>(0.5);
}
