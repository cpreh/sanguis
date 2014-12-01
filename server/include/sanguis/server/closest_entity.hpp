#ifndef SANGUIS_SERVER_CLOSEST_ENTITY_HPP_INCLUDED
#define SANGUIS_SERVER_CLOSEST_ENTITY_HPP_INCLUDED

#include <sanguis/server/space_unit.hpp>
#include <sanguis/server/collision/distance_entity_entity.hpp>
#include <sanguis/server/entities/base.hpp>
#include <fcppt/optional_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <limits>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace server
{

// TODO: Use optionals!
template<
	typename Container,
	typename Predicate
>
fcppt::optional<
	typename
	Container::value_type::type &
> const
closest_entity(
	sanguis::server::entities::base const &_ref,
	Container const &_entities,
	Predicate const _predicate
)
{
	typedef
	fcppt::optional<
		typename
		Container::value_type::type &
	>
	result_type;

	result_type ret;

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
				entity.get()
			)
		);

		if(
			_predicate(
				entity.get()
			)
			&&
			new_distance
			<
			distance
		)
		{
			distance =
				new_distance;

			ret =
				result_type(
					entity.get()
				);
		}
	}

	return
		ret;
}

}
}

#endif
