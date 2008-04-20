#include "simple.hpp"
#include "../entity.hpp"
#include <sge/math/angle.hpp>
#include <boost/foreach.hpp>

sanguis::server::ai::simple::simple(
	entity &me)
: me(me),
  target(0)
{}

void sanguis::server::ai::simple::update(
	time_type,
	entity_container const &entities)
{
	if(!target)
	{
		BOOST_FOREACH(
			entity const &e,
			entities)
		{
			if(e.type() == entity_type::player)
				target = &e;
		}
	}
	if(!target)
		return;

	const boost::optional<messages::space_unit> angle(
		sge::math::angle_to<messages::space_unit>(
			me.center(),
			target->center()));
	if(angle)
		me.angle(*angle);
	me.speed(messages::mu(1));
}
