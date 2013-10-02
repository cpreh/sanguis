#include <sanguis/creator/aux_/reachable.hpp>
#include <sanguis/creator/aux_/reachable_grid.hpp>
#include <sanguis/creator/grid.hpp>
#include <sanguis/creator/pos.hpp>
#include <sanguis/creator/tile_is_solid.hpp>
#include <fcppt/container/grid/neumann_neighbors.hpp>
#include <fcppt/container/grid/object.hpp>

fcppt::container::grid::object<
	sanguis::creator::aux_::reachable,
	2
>
sanguis::creator::aux_::reachable_grid(
	sanguis::creator::grid const &_grid,
	sanguis::creator::pos const _start
)
{
	typedef
	fcppt::container::grid::object<
		sanguis::creator::aux_::reachable,
		2
	>
	grid_type;

	grid_type
	result(
		grid_type::dim(
			_grid.size()),
		sanguis::creator::aux_::reachable(
			false)
	);

	std::vector<
		sanguis::creator::pos
	> queue;

	queue.push_back(
		_start);

	while(
		!queue.empty()
	)
	{
		sanguis::creator::pos
		pos =
			queue.back();

		queue.pop_back();

		result
		[
			pos
		] =
			true;

		for(
			auto const &n :
			fcppt::container::grid::neumann_neighbors(
				pos)
		)
			if(
					result
					[
						n
					]
					.get()
				==
					false
				&&
					!sanguis::creator::tile_is_solid(
						_grid
						[
							n
						]
					)
			)
				queue.push_back(n);
	}

	return result;
}
