#ifndef SANGUIS_TILES_IMPL_NEIGHBORS_TO_STRING_HPP_INCLUDED
#define SANGUIS_TILES_IMPL_NEIGHBORS_TO_STRING_HPP_INCLUDED

#include <sanguis/creator/enable_if_tile.hpp>
#include <sanguis/creator/instantiate_tile.hpp>
#include <sanguis/tiles/impl/neighbors_fwd.hpp>
#include <fcppt/string.hpp>

namespace sanguis::tiles::impl
{

template <typename Tile>
sanguis::creator::enable_if_tile<Tile, fcppt::string>
neighbors_to_string(sanguis::tiles::impl::neighbors<Tile> const &);

}

#define SANGUIS_TILES_DECLARE_NEIGHBORS_TO_STRING(tile_type) \
  extern template sanguis::creator::enable_if_tile<tile_type, fcppt::string> \
  sanguis::tiles::impl::neighbors_to_string(sanguis::tiles::impl::neighbors<tile_type> const &)

SANGUIS_CREATOR_INSTANTIATE_TILE(SANGUIS_TILES_DECLARE_NEIGHBORS_TO_STRING);

#endif
