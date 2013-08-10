#ifndef SANGUIS_SERVER_CLOSEST_ENTITY_HPP_INCLUDED
#define SANGUIS_SERVER_CLOSEST_ENTITY_HPP_INCLUDED

#include <sanguis/server/space_unit.hpp>
#include <sanguis/server/collision/distance_entity_entity.hpp>
#include <sanguis/server/entities/base.hpp>
#include <fcppt/config/external_begin.hpp>
#include <limits>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace server
{

// TODO: Use optionals!
template<
	typename Container
>
typename Container::value_type
closest_entity(
	sanguis::server::entities::base const &_ref,
	Container const &_entities
)
{
	typedef
	typename
	Container::value_type
	value_type;

	value_type ret = nullptr;

	sanguis::server::space_unit distance(
		std::numeric_limits<
			sanguis::server::space_unit
		>::max()
	);

	for(
		auto const entity
		:
		_entities
	)
	{
		sanguis::server::space_unit const new_distance(
			sanguis::server::collision::distance_entity_entity(
				_ref,
				*entity
			)
		);

		if(
			new_distance < distance
		)
		{
			distance = new_distance;

			ret = entity;
		}
	}

	return ret;
}

}
}

#endif
