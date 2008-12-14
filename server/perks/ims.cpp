#include "ims.hpp"
#include "../entities/entity.hpp"

void sanguis::server::perks::ims::do_apply(
	entities::entity &e)
{
	e.get_property(
		entities::property::type::movement_speed)
		.multiply_max_with_base(factor());
}

bool sanguis::server::perks::ims::can_raise_level() const
{
	return true;
}

sanguis::messages::space_unit
sanguis::server::perks::ims::factor() const
{
	return messages::mu(1)
		+ static_cast<messages::space_unit>(level())
		* messages::mu(0.1);
}
