#include <sanguis/tiles/impl/background_tile_name.hpp>
#include <sanguis/creator/background_tile.hpp>
#include <fcppt/string.hpp>
#include <fcppt/assert/unreachable.hpp>

fcppt::string
sanguis::tiles::impl::background_tile_name(sanguis::creator::background_tile const _tile)
{
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

  FCPPT_ASSERT_UNREACHABLE;
}
