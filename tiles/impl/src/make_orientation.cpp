#include <sanguis/creator/enable_if_tile.hpp>
#include <sanguis/creator/instantiate_tile.hpp>
#include <sanguis/tiles/direction.hpp>
#include <sanguis/tiles/exception.hpp>
#include <sanguis/tiles/orientation.hpp>
#include <sanguis/tiles/pair.hpp>
#include <sanguis/tiles/impl/make_orientation.hpp>
#include <sanguis/tiles/impl/neighbors.hpp>
#include <fcppt/not.hpp>
#include <fcppt/text.hpp>
#include <fcppt/enum/make_range.hpp>

template <typename Tile>
sanguis::creator::enable_if_tile<Tile, sanguis::tiles::orientation>
sanguis::tiles::impl::make_orientation(
    sanguis::tiles::pair<Tile> const &_pair,
    sanguis::tiles::impl::neighbors<Tile> const &_neighbors)
{
  sanguis::tiles::orientation orientation{sanguis::tiles::orientation::null()};

  // TODO(philipp): Check if the tile is _pair.second?
  for (sanguis::tiles::direction const value :
       fcppt::enum_::make_range<sanguis::tiles::direction>())
  {
    Tile const tile{_neighbors[value]};

    if (fcppt::not_(tile == _pair.first() || tile == _pair.second()))
    {
      throw sanguis::tiles::exception{FCPPT_TEXT("Invalid tile neighbor!")};
    }

    orientation[value] = tile == _pair.first();
  }

  return orientation;
}

#define SANGUIS_TILES_INSTANTIATE_MAKE_ORIENTATION(tile_type) \
  template sanguis::creator::enable_if_tile<tile_type, sanguis::tiles::orientation> \
  sanguis::tiles::impl::make_orientation( \
      sanguis::tiles::pair<tile_type> const &, sanguis::tiles::impl::neighbors<tile_type> const &)

SANGUIS_CREATOR_INSTANTIATE_TILE(SANGUIS_TILES_INSTANTIATE_MAKE_ORIENTATION);
