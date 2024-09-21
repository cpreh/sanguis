#ifndef SANGUIS_CREATOR_BACKGROUND_TILE_HPP_INCLUDED
#define SANGUIS_CREATOR_BACKGROUND_TILE_HPP_INCLUDED

#include <sanguis/creator/background_tile_fwd.hpp> // IWYU pragma: keep
#include <fcppt/enum/define_max_value.hpp>

namespace sanguis::creator
{

// NOLINTNEXTLINE(performance-enum-size)
enum class background_tile
{
  asphalt,
  dirt,
  grass,
  nothing
};

}

FCPPT_ENUM_DEFINE_MAX_VALUE(sanguis::creator::background_tile::nothing);

#endif
