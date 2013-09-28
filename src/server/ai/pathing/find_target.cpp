#include <sanguis/creator/grid.hpp>
#include <sanguis/creator/pos.hpp>
#include <sanguis/creator/tile_is_solid.hpp>
#include <sanguis/server/ai/pathing/find_target.hpp>
#include <sanguis/server/ai/pathing/start.hpp>
#include <sanguis/server/ai/pathing/target.hpp>
#include <sanguis/server/ai/pathing/trail.hpp>
#include <fcppt/container/grid/in_range.hpp>
#include <fcppt/container/grid/neumann_neighbors.hpp>
#include <fcppt/container/grid/object_impl.hpp>
#include <fcppt/math/vector/comparison.hpp>
#include <fcppt/math/vector/std_hash.hpp>
#include <fcppt/config/external_begin.hpp>
#include <queue>
#include <unordered_map>
#include <utility>
#include <fcppt/config/external_end.hpp>


sanguis::server::ai::pathing::trail
sanguis::server::ai::pathing::find_target(
	sanguis::creator::grid const &_grid,
	sanguis::server::ai::pathing::start const _start,
	sanguis::server::ai::pathing::target const _target
)
{
	typedef
	std::queue<
		sanguis::creator::pos
	>
	pos_queue;

	typedef
	fcppt::container::grid::object<
		bool,
		2
	>
	marker_grid;

	typedef
	std::unordered_map<
		sanguis::creator::pos,
		sanguis::creator::pos
	>
	predecessor_map;

	predecessor_map predecessors;

	marker_grid markers(
		_grid.size(),
		false
	);

	pos_queue positions;

	positions.push(
		_start.get()
	);

	while(
		!positions.empty()
	)
	{
		sanguis::creator::pos const cur(
			positions.front()
		);

		if(
			cur == _target.get()
		)
		{
			sanguis::server::ai::pathing::trail result{
				cur
			};

			for(
				sanguis::creator::pos trail_pos(
					cur
				);
				trail_pos
				!=
				_start.get();
				trail_pos
				=
				result.back()
			)
				result.push_back(
					predecessors[
						trail_pos
					]
				);

			return
				result;
		}

		positions.pop();

		markers[
			cur
		] = true;

		for(
			auto const &pos
			:
			fcppt::container::grid::neumann_neighbors(
				cur
			)
		)
			if(
				fcppt::container::grid::in_range(
					_grid,
					pos
				)
				&&
				!markers[
					pos
				]
				&&
				!sanguis::creator::tile_is_solid(
					_grid[
						pos
					]
				)
			)
			{
				positions.push(
					pos
				);

				predecessors.insert(
					std::make_pair(
						pos,
						cur
					)
				);
			}
	}

	return
		sanguis::server::ai::pathing::trail();
}
