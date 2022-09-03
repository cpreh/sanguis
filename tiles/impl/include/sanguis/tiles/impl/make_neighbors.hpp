#ifndef SANGUIS_TILES_IMPL_MAKE_NEIGHBORS_HPP_INCLUDED
#define SANGUIS_TILES_IMPL_MAKE_NEIGHBORS_HPP_INCLUDED

#include <sanguis/creator/enable_if_tile.hpp>
#include <sanguis/creator/instantiate_tile.hpp>
#include <sanguis/creator/pos_fwd.hpp>
#include <sanguis/creator/tile_grid_fwd.hpp>
#include <sanguis/tiles/impl/neighbors.hpp>
#include <fcppt/optional/object_impl.hpp>

namespace sanguis::tiles::impl
{

template <typename Tile>
sanguis::creator::
    enable_if_tile<Tile, fcppt::optional::object<sanguis::tiles::impl::neighbors<Tile>>>
    make_neighbors(sanguis::creator::tile_grid<Tile> const &, sanguis::creator::pos const &);
}

#define SANGUIS_TILES_DECLARE_MAKE_NEIGHBORS(tile_type) \
  extern template sanguis::creator:: \
      enable_if_tile<tile_type, fcppt::optional::object<sanguis::tiles::impl::neighbors<tile_type>>> \
      sanguis::tiles::impl::make_neighbors( \
          sanguis::creator::tile_grid<tile_type> const &, sanguis::creator::pos const &)

SANGUIS_CREATOR_INSTANTIATE_TILE(SANGUIS_TILES_DECLARE_MAKE_NEIGHBORS);

#endif
