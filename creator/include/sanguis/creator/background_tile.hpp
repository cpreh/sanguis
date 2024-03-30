#ifndef SANGUIS_CREATOR_BACKGROUND_TILE_HPP_INCLUDED
#define SANGUIS_CREATOR_BACKGROUND_TILE_HPP_INCLUDED

#include <sanguis/creator/background_tile_fwd.hpp> // IWYU pragma: keep

namespace sanguis::creator
{

// NOLINTNEXTLINE(performance-enum-size)
enum class background_tile
{
  asphalt,
  dirt,
  grass,
  nothing,
  fcppt_maximum = nothing
};

}

#endif
