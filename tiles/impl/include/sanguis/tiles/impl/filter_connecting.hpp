#ifndef SANGUIS_TILES_IMPL_FILTER_CONNECTING_HPP_INCLUDED
#define SANGUIS_TILES_IMPL_FILTER_CONNECTING_HPP_INCLUDED

#include <sanguis/tiles/pair.hpp>
#include <sanguis/creator/background_tile.hpp>
#include <sanguis/creator/tile.hpp>

namespace sanguis::tiles::impl
{

inline bool filter_connecting(sanguis::tiles::pair<sanguis::creator::tile> const _pair)
{
  return _pair.first() == sanguis::creator::tile::nothing &&
         _pair.second() == sanguis::creator::tile::nothing;
}

inline bool filter_connecting(sanguis::tiles::pair<sanguis::creator::background_tile>)
{
  return false;
}

}

#endif
