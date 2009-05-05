#include "simple.hpp"
#include "../entities/entity_with_weapon.hpp"
#include "../entities/property.hpp"
#include "../collision/collides.hpp"
#include "../collision/distance.hpp"
#include <sge/time/second.hpp>
#include <sge/time/resolution.hpp>
#include <sge/optional.hpp>
#include <sge/math/angle.hpp>
#include <boost/foreach.hpp>
#include <limits>

sanguis::server::ai::simple::simple()
:
	me_(0),
	target(),
	diff_clock_(),
	search_new_target_timer(
		sge::time::second(
			5
		),
		sge::time::activation_state::active,
		diff_clock_.callback()
	)
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

	entities::property &speed(
		me.property(
			entities::property_type::movement_speed
		)
	);

	if(search_new_target_timer.update_b() || !target)
	{
		space_unit distance(
			std::numeric_limits<
				space_unit
			>::max());

		BOOST_FOREACH(
			entities::entity &e,
			entities)
		{
			if(e.invulnerable() || e.team() == me.team())
				continue;

			space_unit const new_distance(
				collision::distance(
					me,
					e
				)
			);

			if(new_distance >= distance)
				continue;

			distance = new_distance;
			target = me.link(e);
		}

		if(!target)
		{
			me.aggressive(false);
			speed.current(
				static_cast<space_unit>(0));
			return;
		}

		me.aggressive(true);
	}

	sge::optional<space_unit> const angle(
		sge::math::angle_to<space_unit>(
			me.center(),
			target->center()
		)
	);

	if(angle)
	{
		me.direction(*angle);
		me.angle(*angle);
	}
	
	if(collision::collides(*target, me))
		speed.current(
			static_cast<space_unit>(0));
	else
		speed.current_to_max();

	me.target(
		target->center());
}
