#ifndef SANGUIS_CREATOR_IMPL_BLIT_HPP_INCLUDED
#define SANGUIS_CREATOR_IMPL_BLIT_HPP_INCLUDED

#include <sanguis/creator/enable_if_tile.hpp>
#include <sanguis/creator/tile_grid_fwd.hpp>
#include <fcppt/container/grid/pos_ref_range_fwd.hpp>

namespace sanguis::creator::impl
{

template <typename Tile>
sanguis::creator::enable_if_tile<Tile, void> blit(
    fcppt::container::grid::pos_ref_range<sanguis::creator::tile_grid<Tile>>,
    fcppt::container::grid::pos_ref_range<sanguis::creator::tile_grid<Tile> const>);

}

#endif
