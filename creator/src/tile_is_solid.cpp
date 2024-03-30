#include <sanguis/creator/tile.hpp>
#include <sanguis/creator/tile_is_solid.hpp>
#include <fcppt/enum/make_invalid.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>

bool sanguis::creator::tile_is_solid(sanguis::creator::tile const _tile)
{
  FCPPT_PP_PUSH_WARNING
  FCPPT_PP_DISABLE_GCC_WARNING(-Wswitch-default)
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
  FCPPT_PP_POP_WARNING

  throw fcppt::enum_::make_invalid(_tile);
}
