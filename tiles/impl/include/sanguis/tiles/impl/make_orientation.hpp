#ifndef SANGUIS_TILES_IMPL_MAKE_ORIENTATION_HPP_INCLUDED
#define SANGUIS_TILES_IMPL_MAKE_ORIENTATION_HPP_INCLUDED

#include <sanguis/creator/enable_if_tile.hpp>
#include <sanguis/creator/instantiate_tile.hpp>
#include <sanguis/tiles/orientation.hpp>
#include <sanguis/tiles/pair_fwd.hpp>
#include <sanguis/tiles/impl/neighbors_fwd.hpp>

namespace sanguis::tiles::impl
{

template <typename Tile>
sanguis::creator::enable_if_tile<Tile, sanguis::tiles::orientation>
make_orientation(sanguis::tiles::pair<Tile> const &, sanguis::tiles::impl::neighbors<Tile> const &);

}

#define SANGUIS_TILES_DECLARE_MAKE_ORIENTATION(tile_type) \
  extern template sanguis::creator::enable_if_tile<tile_type, sanguis::tiles::orientation> \
  sanguis::tiles::impl::make_orientation( \
      sanguis::tiles::pair<tile_type> const &, sanguis::tiles::impl::neighbors<tile_type> const &)

SANGUIS_CREATOR_INSTANTIATE_TILE(SANGUIS_TILES_DECLARE_MAKE_ORIENTATION);

#endif
