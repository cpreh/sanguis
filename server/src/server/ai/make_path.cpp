#include <sanguis/creator/grid.hpp>
#include <sanguis/creator/pos.hpp>
#include <sanguis/creator/tile.hpp>
#include <sanguis/creator/tile_is_solid.hpp>
#include <sanguis/server/ai/context.hpp>
#include <sanguis/server/ai/make_path.hpp>
#include <fcppt/const.hpp>
#include <fcppt/reference.hpp>
#include <fcppt/container/grid/at_optional.hpp>
#include <fcppt/optional/maybe.hpp>

bool sanguis::server::ai::make_path(
    sanguis::server::ai::context &_context, sanguis::creator::pos const &_pos)
{
  return fcppt::optional::maybe(
      fcppt::container::grid::at_optional(_context.grid(), _pos),
      fcppt::const_(false),
      [_pos, &_context](fcppt::reference<sanguis::creator::tile const> const _tile)
      { return !sanguis::creator::tile_is_solid(_tile.get()) && _context.path_find(_pos); });
}
