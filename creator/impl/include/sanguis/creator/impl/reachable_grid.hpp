#ifndef SANGUIS_CREATOR_IMPL_REACHABLE_GRID_HPP_INCLUDED
#define SANGUIS_CREATOR_IMPL_REACHABLE_GRID_HPP_INCLUDED

#include <sanguis/creator/tile_grid.hpp>
#include <sanguis/creator/impl/reachable.hpp>

namespace sanguis
{
namespace creator
{
namespace impl
{

typedef
sanguis::creator::tile_grid<
	sanguis::creator::impl::reachable
>
reachable_grid;

}
}
}

#endif
