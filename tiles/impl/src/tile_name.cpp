#include <sanguis/creator/tile.hpp>
#include <sanguis/tiles/impl/tile_name.hpp>
#include <fcppt/string.hpp>
#include <fcppt/text.hpp>
#include <fcppt/enum/make_invalid.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>

fcppt::string sanguis::tiles::impl::tile_name(sanguis::creator::tile const _tile)
{
  // TODO(philipp): Use a macro here
  FCPPT_PP_PUSH_WARNING
  FCPPT_PP_DISABLE_GCC_WARNING(-Wswitch-default)
  switch (_tile)
  {
  case sanguis::creator::tile::concrete_wall:
    return FCPPT_TEXT("concrete_wall");
  case sanguis::creator::tile::stairs:
    return FCPPT_TEXT("stairs");
  case sanguis::creator::tile::grave1:
    return FCPPT_TEXT("grave1");
  case sanguis::creator::tile::grave2:
    return FCPPT_TEXT("grave2");
  case sanguis::creator::tile::grave3:
    return FCPPT_TEXT("grave3");
  case sanguis::creator::tile::grave4:
    return FCPPT_TEXT("grave4");
  case sanguis::creator::tile::grave5:
    return FCPPT_TEXT("grave5");
  case sanguis::creator::tile::hedge:
    return FCPPT_TEXT("hedge");
  case sanguis::creator::tile::spawner:
    return FCPPT_TEXT("spawner");
  case sanguis::creator::tile::nothing:
    return FCPPT_TEXT("nothing");
  }
  FCPPT_PP_POP_WARNING

  throw fcppt::enum_::make_invalid(_tile);
}
