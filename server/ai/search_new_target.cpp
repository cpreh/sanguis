#include "search_new_target.hpp"
#include "../entities/auto_weak_link.hpp"
#include "../entities/base.hpp"
#include "../collision/distance.hpp"
#include <fcppt/container/map_impl.hpp>
#include <sge/assert.hpp>
#include <boost/foreach.hpp>
#include <limits>

sanguis::server::entities::auto_weak_link const
sanguis::server::ai::search_new_target(
	entities::base const &me_,
	entities::auto_weak_link const owner_,
	entity_map const &entities_
)
{
	space_unit distance(
		std::numeric_limits<
			space_unit
		>::max()
	);

	entities::auto_weak_link ret;

	BOOST_FOREACH(
		entity_map::const_reference ref,
		entities_
	)
	{
		entities::auto_weak_link link(
			ref.second
		);

		if(!link)
			continue; // TODO: can this happen?

		space_unit const new_distance(
			owner_
			?
				collision::distance(
					*owner_,
					*link
				)
			:
				collision::distance(
					me_,
					*link
				)
		);

		if(
			new_distance < distance
		)
		{
			distance = new_distance;

			ret = link;
		}
	}

	FCPPT_ASSERT(
		ret
		&& !ret->invulnerable()
	);

	return ret;
}
