#ifndef SANGUIS_TILES_IMPL_TO_STRING_HPP_INCLUDED
#define SANGUIS_TILES_IMPL_TO_STRING_HPP_INCLUDED

#include <sanguis/creator/enable_if_tile.hpp>
#include <sanguis/creator/instantiate_tile.hpp>
#include <fcppt/string.hpp>

namespace sanguis::tiles::impl
{

template <typename Tile>
sanguis::creator::enable_if_tile<Tile, fcppt::string> to_string(Tile);

}

#define SANGUIS_TILES_DECLARE_TO_STRING(tile_type) \
  extern template sanguis::creator::enable_if_tile<tile_type, fcppt::string> \
  sanguis::tiles::impl::to_string(tile_type)

SANGUIS_CREATOR_INSTANTIATE_TILE(SANGUIS_TILES_DECLARE_TO_STRING);

#endif
