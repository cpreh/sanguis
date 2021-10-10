#ifndef SANGUIS_TILES_PAIR_COMPARISON_HPP_INCLUDED
#define SANGUIS_TILES_PAIR_COMPARISON_HPP_INCLUDED

#include <sanguis/creator/enable_if_tile.hpp>
#include <sanguis/tiles/pair_fwd.hpp>

namespace sanguis::tiles
{

template <typename Tile>
sanguis::creator::enable_if_tile<Tile, bool>
operator==(sanguis::tiles::pair<Tile>, sanguis::tiles::pair<Tile>);

}

#endif
