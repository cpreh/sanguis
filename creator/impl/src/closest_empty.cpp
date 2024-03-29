#include <sanguis/creator/grid_fwd.hpp>
#include <sanguis/creator/pos.hpp>
#include <sanguis/creator/tile.hpp>
#include <sanguis/creator/impl/closest_empty.hpp>
#include <sanguis/creator/impl/find_closest.hpp>
#include <sanguis/creator/impl/optional_pos.hpp>
#include <fcppt/optional/object.hpp>

sanguis::creator::impl::optional_pos sanguis::creator::impl::closest_empty(
    sanguis::creator::grid const &_grid, sanguis::creator::pos const &_pos)
{
  return sanguis::creator::impl::find_closest(
      _grid,
      _pos,
      [](sanguis::creator::pos const &, sanguis::creator::tile const _tile)
      {
        return _tile == sanguis::creator::tile::nothing;
      },
      fcppt::optional::object<sanguis::creator::pos::value_type>{});
}
