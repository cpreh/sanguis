#include "search_new_target.hpp"
#include "../entities/auto_weak_link.hpp"
#include "../entities/base.hpp"
#include "../collision/distance.hpp"
#include <fcppt/container/map_impl.hpp>
#include <fcppt/assert.hpp>
#include <boost/foreach.hpp>
#include <limits>

sanguis::server::entities::auto_weak_link const
sanguis::server::ai::search_new_target(
	entities::base const &_me,
	entities::auto_weak_link const _owner,
	entity_map const &_entities
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
		_entities
	)
	{
		entities::auto_weak_link link(
			ref.second
		);

		if(
			!link
		)
			continue; // TODO: can this happen?

		space_unit const new_distance(
			_owner
			?
				collision::distance(
					*_owner,
					*link
				)
			:
				collision::distance(
					_me,
					*link
				)
		);

		if(
			new_distance < distance
			&& !link->invulnerable()
		)
		{
			distance = new_distance;

			ret = link;
		}
	}

	FCPPT_ASSERT(
		!ret
		|| !ret->invulnerable()
	);

	return ret;
}
