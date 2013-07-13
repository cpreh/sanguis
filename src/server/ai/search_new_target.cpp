#include <sanguis/server/space_unit.hpp>
#include <sanguis/server/ai/entity_set.hpp>
#include <sanguis/server/ai/search_new_target.hpp>
#include <sanguis/server/entities/auto_weak_link.hpp>
#include <sanguis/server/entities/base.hpp>
#include <sanguis/server/entities/with_health.hpp>
#include <sanguis/server/collision/distance.hpp>
#include <fcppt/config/external_begin.hpp>
#include <limits>
#include <fcppt/config/external_end.hpp>


sanguis::server::entities::auto_weak_link const
sanguis::server::ai::search_new_target(
	sanguis::server::entities::base const &_me,
	sanguis::server::ai::entity_set const &_entities
)
{
	sanguis::server::space_unit distance(
		std::numeric_limits<
			sanguis::server::space_unit
		>::max()
	);

	sanguis::server::entities::auto_weak_link ret;

	for(
		auto const entity
		:
		_entities
	)
	{
		sanguis::server::space_unit const new_distance(
			sanguis::server::collision::distance(
				_me,
				*entity
			)
		);

		if(
			new_distance < distance
		)
		{
			distance = new_distance;

			ret = entity->link();
		}
	}

	return ret;
}
