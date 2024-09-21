#ifndef SANGUIS_TILES_DIRECTION_HPP_INCLUDED
#define SANGUIS_TILES_DIRECTION_HPP_INCLUDED

#include <sanguis/tiles/direction_fwd.hpp> // IWYU pragma: keep
#include <fcppt/enum/define_max_value.hpp>
#include <fcppt/config/external_begin.hpp>
#include <cstdint>
#include <fcppt/config/external_end.hpp>

namespace sanguis::tiles
{

enum class direction : std::uint8_t
{
  north_west,
  north_east,
  south_west,
  south_east
};

}

FCPPT_ENUM_DEFINE_MAX_VALUE(sanguis::tiles::direction::south_east);

#endif
