#ifndef SANGUIS_TILES_ERROR_HPP_INCLUDED
#define SANGUIS_TILES_ERROR_HPP_INCLUDED

#include <sanguis/tiles/error_fwd.hpp> // IWYU pragma: keep
#include <fcppt/enum/define_max_value.hpp>
#include <fcppt/config/external_begin.hpp>
#include <cstdint>
#include <fcppt/config/external_end.hpp>

namespace sanguis::tiles
{

enum class error : std::uint8_t
{
  missing_foreground,
  missing_background,
  missing_object
};

}

FCPPT_ENUM_DEFINE_MAX_VALUE(sanguis::tiles::error::missing_object);

#endif
