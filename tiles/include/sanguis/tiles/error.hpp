#ifndef SANGUIS_TILES_ERROR_HPP_INCLUDED
#define SANGUIS_TILES_ERROR_HPP_INCLUDED

#include <sanguis/tiles/error_fwd.hpp>

namespace sanguis::tiles
{

enum class error
{
  missing_foreground,
  missing_background,
  missing_object,
  fcppt_maximum = missing_object
};

}

#endif
