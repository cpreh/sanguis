#ifndef SANGUIS_CREATOR_TILE_HPP_INCLUDED
#define SANGUIS_CREATOR_TILE_HPP_INCLUDED

#include <sanguis/creator/tile_fwd.hpp> // IWYU pragma: keep
#include <fcppt/enum/define_max_value.hpp>

namespace sanguis::creator
{

// NOLINTNEXTLINE(performance-enum-size)
enum class tile
{
  nothing,
  stairs,
  spawner,
  grave1,
  grave2,
  grave3,
  grave4,
  grave5,
  hedge,
  concrete_wall
};

}

FCPPT_ENUM_DEFINE_MAX_VALUE(sanguis::creator::tile::concrete_wall);

#endif
