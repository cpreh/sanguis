#include <sanguis/creator/enable_if_tile.hpp>
#include <sanguis/creator/instantiate_tile.hpp>
#include <sanguis/tiles/pair_comparison.hpp>
#include <sanguis/tiles/pair.hpp>

template <typename Tile>
sanguis::creator::enable_if_tile<Tile, bool> sanguis::tiles::operator==(
    sanguis::tiles::pair<Tile> const _left, sanguis::tiles::pair<Tile> const _right)
{
  return _left.first() == _right.first() && _left.second() == _right.second();
}

#define SANGUIS_TILES_INSTANTIATE_TILE_EQUAL(tile_type) \
  template sanguis::creator::enable_if_tile<tile_type, bool> sanguis::tiles::operator==( \
      sanguis::tiles::pair<tile_type>, sanguis::tiles::pair<tile_type>)

SANGUIS_CREATOR_INSTANTIATE_TILE(SANGUIS_TILES_INSTANTIATE_TILE_EQUAL);
