#include <sanguis/creator/grid.hpp>
#include <sanguis/creator/pos.hpp>
#include <sanguis/creator/signed_pos.hpp>
#include <sanguis/creator/tile.hpp>
#include <sanguis/creator/tile_is_solid.hpp>
#include <sanguis/server/ai/pathing/can_walk_diagonally.hpp>
#include <sanguis/server/ai/pathing/positions_are_close.hpp>
#include <fcppt/const.hpp>
#include <fcppt/not.hpp>
#include <fcppt/container/grid/at_optional.hpp>
#include <fcppt/math/dim/contents.hpp>
#include <fcppt/math/vector/arithmetic.hpp>
#include <fcppt/math/vector/to_dim.hpp>
#include <fcppt/math/vector/to_signed.hpp>
#include <fcppt/math/vector/to_unsigned.hpp>
#include <fcppt/optional/copy_value.hpp>
#include <fcppt/optional/maybe.hpp>

bool sanguis::server::ai::pathing::can_walk_diagonally(
    sanguis::creator::grid const &_grid,
    sanguis::creator::pos const &_pos1,
    sanguis::creator::pos const &_pos2,
    sanguis::creator::pos const &_pos3)
{
  if (fcppt::not_(sanguis::server::ai::pathing::positions_are_close(_pos1, _pos2)))
  {
    return false;
  }

  if (fcppt::not_(sanguis::server::ai::pathing::positions_are_close(_pos2, _pos3)))
  {
    return false;
  }

  sanguis::creator::signed_pos const spos1(fcppt::math::vector::to_signed(_pos1));

  sanguis::creator::signed_pos const spos2(fcppt::math::vector::to_signed(_pos2));

  sanguis::creator::signed_pos const spos3(fcppt::math::vector::to_signed(_pos3));

  sanguis::creator::signed_pos const diff(spos1 - spos3);

  if (fcppt::math::dim::contents(fcppt::math::vector::to_dim(diff)) == 0)
  {
    return true;
  }

  sanguis::creator::signed_pos const spos4(
      (spos2 - spos3).x() != 0 ? sanguis::creator::signed_pos(spos3.x() + diff.x(), spos3.y())
                               : sanguis::creator::signed_pos(spos3.x(), spos3.y() + diff.y()));

  return fcppt::optional::maybe(
      fcppt::optional::copy_value(
          fcppt::container::grid::at_optional(_grid, fcppt::math::vector::to_unsigned(spos4))),
      fcppt::const_(true),
      [](sanguis::creator::tile const _tile) { return !sanguis::creator::tile_is_solid(_tile); });
}
