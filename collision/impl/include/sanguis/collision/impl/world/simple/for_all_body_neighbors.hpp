#ifndef SANGUIS_COLLISION_IMPL_WORLD_SIMPLE_FOR_ALL_BODY_NEIGHBORS_HPP_INCLUDED
#define SANGUIS_COLLISION_IMPL_WORLD_SIMPLE_FOR_ALL_BODY_NEIGHBORS_HPP_INCLUDED

#include <sanguis/creator/dim.hpp>
#include <sanguis/creator/pos.hpp>
#include <fcppt/container/array/push_back.hpp>
#include <fcppt/container/grid/in_range_dim.hpp>
#include <fcppt/container/grid/moore_neighbors.hpp>


namespace sanguis
{
namespace collision
{
namespace impl
{
namespace world
{
namespace simple
{

template<
	typename Function
>
void
for_all_body_neighbors(
	sanguis::creator::pos const _pos,
	sanguis::creator::dim const _size,
	Function const &_function
)
{
	for(
		sanguis::creator::pos const grid_pos2
		:
		fcppt::container::array::push_back(
			fcppt::container::grid::moore_neighbors(
				_pos
			),
			_pos
		)
	)
	{
		if(
			fcppt::container::grid::in_range_dim(
				_size,
				grid_pos2
			)
		)
			_function(
				grid_pos2
			);
	}
}

}
}
}
}
}

#endif
