#ifndef SANGUIS_TILES_IMPL_CATEGORY_HPP_INCLUDED
#define SANGUIS_TILES_IMPL_CATEGORY_HPP_INCLUDED

#include <sanguis/creator/enable_if_tile.hpp>
#include <sanguis/creator/instantiate_tile.hpp>
#include <fcppt/string.hpp>

namespace sanguis::tiles::impl
{

template <typename Tile>
sanguis::creator::enable_if_tile<Tile, fcppt::string> category();

}

#define SANGUIS_TILES_DECLARE_CATEGORY(tile_type) \
  extern template sanguis::creator::enable_if_tile<tile_type, fcppt::string> \
  sanguis::tiles::impl::category<tile_type>()

SANGUIS_CREATOR_INSTANTIATE_TILE(SANGUIS_TILES_DECLARE_CATEGORY);

#endif
