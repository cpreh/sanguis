#include <sanguis/server/ai/search_new_target.hpp>
#include <sanguis/server/entities/auto_weak_link.hpp>
#include <sanguis/server/entities/base.hpp>
#include <sanguis/server/entities/with_health.hpp>
#include <sanguis/server/collision/distance.hpp>
#include <fcppt/container/map_impl.hpp>
#include <fcppt/math/vector/basic_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <limits>
#include <fcppt/config/external_end.hpp>

sanguis::server::entities::auto_weak_link const
sanguis::server::ai::search_new_target(
	entities::base const &_me,
	ai::entity_map const &_entities
)
{
	space_unit distance(
		std::numeric_limits<
			space_unit
		>::max()
	);

	entities::auto_weak_link ret;

	for(
		entity_map::const_iterator it(
			_entities.begin()
		);
		it != _entities.end();
		++it
	)
	{
		entities::with_health &target(
			*it->second
		);

		space_unit const new_distance(
			collision::distance(
				_me,
				target
			)
		);

		if(
			new_distance < distance
		)
		{
			distance = new_distance;

			ret = target.link();
		}
	}

	return ret;
}
