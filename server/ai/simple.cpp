#include "simple.hpp"
#include "../entity.hpp"
#include "../entities/enemy.hpp"
#include <sge/math/angle.hpp>
#include <boost/foreach.hpp>

sanguis::server::ai::simple::simple(
	entities::enemy &me)
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
	else
	{
		// TODO: why can't we use std::find here?
		for(entity_container::const_iterator it(entities.begin()); it != entities.end(); ++it)
			if(&*it == target)
				break;
		target = 0;
	}

	if(!target)
		return;

	const boost::optional<messages::space_unit> angle(
		sge::math::angle_to<messages::space_unit>(
			me.center(),
			target->center()));
	if(angle)
	{
		me.direction(*angle);
		me.angle(*angle);
	}
	me.speed(messages::mu(1));
	me.target(
		target->center());
	me.aggressive(true);
}
