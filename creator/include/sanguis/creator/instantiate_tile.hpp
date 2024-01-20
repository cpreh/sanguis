#ifndef SANGUIS_CREATOR_INSTANTIATE_TILE_HPP_INCLUDED
#define SANGUIS_CREATOR_INSTANTIATE_TILE_HPP_INCLUDED

#include <sanguis/creator/background_tile.hpp> // IWYU pragma: keep
#include <sanguis/creator/tile.hpp> // IWYU pragma: keep

#define SANGUIS_CREATOR_INSTANTIATE_TILE(macro) \
  macro(sanguis::creator::tile); \
  macro(sanguis::creator::background_tile)

#endif
