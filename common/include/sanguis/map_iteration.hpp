#ifndef SANGUIS_MAP_ITERATION_HPP_INCLUDED
#define SANGUIS_MAP_ITERATION_HPP_INCLUDED


namespace sanguis
{

template<
	typename Map,
	typename UpdateAction,
	typename Predicate,
	typename DestroyAction
>
void
map_iteration(
	Map &_map,
	UpdateAction const &_update_action,
	Predicate const &_predicate,
	DestroyAction const &_destroy_action
)
{
	for(
		typename Map::iterator it(
			_map.begin()
		),
		next(
			it
		);
		it != _map.end();
		it = next
	)
	{
		++next;

		_update_action(
			*it->second
		);

		if(
			_predicate(
				*it->second
			)
		)
		{
			_destroy_action(
				*it->second
			);

			_map.erase(
				it
			);
		}
	}
}

}

#endif
