#include "ims.hpp"
#include "../entity.hpp"

void sanguis::server::perks::ims::do_activate()
{
	entity &e(get_entity());
	e.max_speed(e.max_speed() * factor());
}

void sanguis::server::perks::ims::do_deactivate()
{
	entity &e(get_entity());
	e.max_speed(e.max_speed() / factor());
}

bool sanguis::server::perks::ims::can_raise_level() const
{
	return true;
}

sanguis::messages::space_unit
sanguis::server::perks::ims::factor() const
{
	return static_cast<messages::space_unit>(level()) / messages::mu(0.1); // TODO: make this nonlinear	
}
