#include "find_nearest_enemy.hpp"
#include "../entities/entity.hpp"
#include "../entities/auto_weak_link.hpp"
#include "../collision/distance.hpp"
#include <boost/foreach.hpp>
#include <limits>

sanguis::server::entities::auto_weak_link
sanguis::server::ai::find_nearest_enemy(
	entities::entity &me,
	pos_type const &pos,
	entities::container &entities)
{
	space_unit distance(
		std::numeric_limits<
			space_unit
		>::max()
	);

	entities::auto_weak_link target;

	BOOST_FOREACH(
		entities::entity &e,
		entities
	)
	{
		if(e.invulnerable() || e.team() == me.team())
			continue;

		space_unit const new_distance(
			collision::distance(
				e,
				pos
			)
		);

		if(new_distance >= distance)
			continue;

		distance = new_distance;

		target = e.link();
	}

	return target;
}
