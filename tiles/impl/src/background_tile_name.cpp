#include <sanguis/tiles/impl/background_tile_name.hpp>
#include <sanguis/creator/background_tile.hpp>
#include <fcppt/string.hpp>
#include <fcppt/text.hpp>
#include <fcppt/enum/make_invalid.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>

fcppt::string
sanguis::tiles::impl::background_tile_name(sanguis::creator::background_tile const _tile)
{
  FCPPT_PP_PUSH_WARNING
  FCPPT_PP_DISABLE_GCC_WARNING(-Wswitch-default)
  switch (_tile)
  {
  case sanguis::creator::background_tile::nothing:
    return FCPPT_TEXT("nothing");
  case sanguis::creator::background_tile::asphalt:
    return FCPPT_TEXT("asphalt");
  case sanguis::creator::background_tile::dirt:
    return FCPPT_TEXT("dirt");
  case sanguis::creator::background_tile::grass:
    return FCPPT_TEXT("grass");
  }
  FCPPT_PP_POP_WARNING

  throw fcppt::enum_::make_invalid(_tile);
}
