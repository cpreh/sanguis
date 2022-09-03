#include <sanguis/creator/enable_if_tile.hpp>
#include <sanguis/creator/instantiate_tile.hpp>
#include <sanguis/creator/pos.hpp>
#include <sanguis/creator/tile_grid.hpp>
#include <sanguis/tiles/impl/make_neighbors.hpp>
#include <sanguis/tiles/impl/neighbors.hpp>
#include <sanguis/tiles/impl/replace_non_connecting.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/container/grid/at_optional.hpp>
#include <fcppt/optional/apply.hpp>
#include <fcppt/optional/map.hpp>
#include <fcppt/optional/object_impl.hpp>

template <typename Tile>
sanguis::creator::enable_if_tile<Tile, fcppt::optional::object<sanguis::tiles::impl::neighbors<Tile>>>
sanguis::tiles::impl::make_neighbors(
    sanguis::creator::tile_grid<Tile> const &_grid, sanguis::creator::pos const &_pos)
{
  auto const get_tile{
      [&_grid](sanguis::creator::pos const _npos) -> fcppt::optional::object<Tile>
      {
        return fcppt::optional::map(
            fcppt::container::grid::at_optional(_grid, _npos),
            [](fcppt::reference<Tile const> const _tile)
            { return sanguis::tiles::impl::replace_non_connecting(_tile.get()); });
      }};

  return fcppt::optional::apply(
      [](Tile const _tile1, Tile const _tile2, Tile const _tile3, Tile const _tile4) {
        return sanguis::tiles::impl::neighbors<Tile>{_tile1, _tile2, _tile3, _tile4};
      },
      get_tile(sanguis::creator::pos{_pos.x() - 1, _pos.y() - 1}),
      get_tile(sanguis::creator::pos{_pos.x(), _pos.y() - 1}),
      get_tile(sanguis::creator::pos{_pos.x() - 1, _pos.y()}),
      get_tile(sanguis::creator::pos{_pos.x(), _pos.y()}));
}

#define SANGUIS_TILES_INSTANTIATE_MAKE_NEIGHBORS(tile_type) \
  template sanguis::creator::enable_if_tile< \
      tile_type, \
      fcppt::optional::object<sanguis::tiles::impl::neighbors<tile_type>>> \
  sanguis::tiles::impl::make_neighbors( \
      sanguis::creator::tile_grid<tile_type> const &, sanguis::creator::pos const &)

SANGUIS_CREATOR_INSTANTIATE_TILE(SANGUIS_TILES_INSTANTIATE_MAKE_NEIGHBORS);
