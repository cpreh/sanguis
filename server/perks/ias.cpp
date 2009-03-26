#include "ias.hpp"
#include "../entities/property.hpp"
#include "../entities/entity.hpp"

void sanguis::server::perks::ias::do_apply(
	entities::entity &e,
	time_type,
	environment const &)
{
	e.property(
		entities::property_type::attack_speed)
		.multiply_max(factor());
}

bool sanguis::server::perks::ias::can_raise_level() const
{
	return true;
}

sanguis::messages::space_unit
sanguis::server::perks::ias::factor() const
{
	return static_cast<messages::space_unit>(level())
		* messages::mu(0.1);
}
