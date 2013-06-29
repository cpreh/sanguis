#include <sanguis/collision/merge_intersection.hpp>
#include <sanguis/collision/optional_intersection.hpp>


sanguis::collision::optional_intersection const
sanguis::collision::merge_intersection(
	sanguis::collision::optional_intersection const _first,
	sanguis::collision::optional_intersection const _second
)
{
	if(
		!_first
	)
		return
			_second;

	if(
		!_second
	)
		return
			_first;

	return
		_first->pos()
		<
		_second->pos()
		?
			_first
		:
			_second
		;
}
