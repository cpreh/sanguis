#ifndef SANGUIS_CREATOR_IMPL_REGION_GRID_HPP_INCLUDED
#define SANGUIS_CREATOR_IMPL_REGION_GRID_HPP_INCLUDED

#include <sanguis/creator/tile_grid.hpp>
#include <sanguis/creator/impl/region_id.hpp>

namespace sanguis
{
namespace creator
{
namespace impl
{

typedef
sanguis::creator::tile_grid<
	sanguis::creator::impl::region_id
>
region_grid;

}
}
}

#endif

