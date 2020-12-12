#ifndef SANGUIS_CREATOR_IMPL_MAZE_RESULT_HPP_INCLUDED
#define SANGUIS_CREATOR_IMPL_MAZE_RESULT_HPP_INCLUDED

#include <sanguis/creator/impl/region_grid.hpp>
#include <sanguis/creator/impl/region_id.hpp>

namespace sanguis
{
namespace creator
{
namespace impl
{

struct
maze_result
{
	sanguis::creator::impl::region_grid
	grid;

	sanguis::creator::impl::region_id
	next_id;
};

}
}
}

#endif

