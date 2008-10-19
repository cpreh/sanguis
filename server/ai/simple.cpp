#include "simple.hpp"
#include "../entities/entity_with_weapon.hpp"
#include <sge/math/angle.hpp>
#include <boost/foreach.hpp>

sanguis::server::ai::simple::simple()
:
	me_(0)
{}

void sanguis::server::ai::simple::bind(
	entities::entity_with_weapon &me)
{
	me_ = &me;
}

void sanguis::server::ai::simple::update(
	time_type,
	entities::container &entities)
{
	if(!me_)
		return;
	
	entities::entity_with_weapon &me(
		*me_);

	if(!target)
	{
		BOOST_FOREACH(
			entities::entity &e,
			entities)
		{
			if(!e.invulnerable() && e.team() != me.team())
			{
				target = me.link(e);
				break;
			}
		}

		if(!target)
		{
			me.aggressive(false);
			return;
		}

		me.get_property(
		entities::property::type::movement_speed)
			.set_current_to_max();
		me.aggressive(true);
	}

	boost::optional<messages::space_unit> const angle(
		sge::math::angle_to<messages::space_unit>(
			me.center(),
			target->center()));
	if(angle)
	{
		me.direction(*angle);
		me.angle(*angle);
	}
	

	me.target(
		target->center());
}
