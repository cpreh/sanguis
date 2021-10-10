#include <sanguis/creator/tile.hpp>
#include <sanguis/creator/tile_connects.hpp>
#include <fcppt/assert/unreachable.hpp>

bool sanguis::creator::tile_connects(sanguis::creator::tile const _tile)
{
  switch (_tile)
  {
  case sanguis::creator::tile::nothing:
  case sanguis::creator::tile::stairs:
  case sanguis::creator::tile::spawner:
  case sanguis::creator::tile::grave1:
  case sanguis::creator::tile::grave2:
  case sanguis::creator::tile::grave3:
  case sanguis::creator::tile::grave4:
  case sanguis::creator::tile::grave5:
    return false;
  case sanguis::creator::tile::hedge:
  case sanguis::creator::tile::concrete_wall:
    return true;
  }

  FCPPT_ASSERT_UNREACHABLE;
}
