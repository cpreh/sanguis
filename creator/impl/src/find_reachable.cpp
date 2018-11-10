#include <sanguis/creator/grid.hpp>
#include <sanguis/creator/pos.hpp>
#include <sanguis/creator/tile_is_solid.hpp>
#include <sanguis/creator/impl/find_reachable.hpp>
#include <sanguis/creator/impl/reachable.hpp>
#include <sanguis/creator/impl/reachable_grid.hpp>
#include <fcppt/assert/optional_error.hpp>
#include <fcppt/container/pop_back.hpp>
#include <fcppt/container/grid/at_optional.hpp>
#include <fcppt/container/grid/neumann_neighbors.hpp>
#include <fcppt/container/grid/object.hpp>
#include <fcppt/config/external_begin.hpp>
#include <vector>
#include <fcppt/config/external_end.hpp>


sanguis::creator::impl::reachable_grid
sanguis::creator::impl::find_reachable(
	sanguis::creator::grid const &_grid,
	sanguis::creator::pos const _start
)
{

	sanguis::creator::impl::reachable_grid
	result(
		sanguis::creator::impl::reachable_grid::dim(
			_grid.size()
		),
		sanguis::creator::impl::reachable(
			false
		)
	);

	std::vector<
		sanguis::creator::pos
	> queue{
		_start
	};

	while(
		!queue.empty()
	)
	{
		sanguis::creator::pos const pos(
			FCPPT_ASSERT_OPTIONAL_ERROR(
				fcppt::container::pop_back(
					queue
				)
			)
		);

		FCPPT_ASSERT_OPTIONAL_ERROR(
			fcppt::container::grid::at_optional(
				result,
				pos
			)
		).get() =
			sanguis::creator::impl::reachable{
				true
			};

		for(
			auto const &n
			:
			fcppt::container::grid::neumann_neighbors(
				pos
			)
		)
			if(
				FCPPT_ASSERT_OPTIONAL_ERROR(
					fcppt::container::grid::at_optional(
						result,
						n
					)
				).get()
				==
				sanguis::creator::impl::reachable{
					false
				}
				&&
				!sanguis::creator::tile_is_solid(
					FCPPT_ASSERT_OPTIONAL_ERROR(
						fcppt::container::grid::at_optional(
							_grid,
							n
						)
					).get()
				)
			)
				queue.push_back(
					n
				);
	}

	return
		result;
}
