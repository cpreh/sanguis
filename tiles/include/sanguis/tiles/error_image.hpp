#ifndef SANGUIS_TILES_ERROR_IMAGE_HPP_INCLUDED
#define SANGUIS_TILES_ERROR_IMAGE_HPP_INCLUDED

#include <sanguis/tiles/error_fwd.hpp>
#include <sanguis/tiles/symbol.hpp>
#include <sge/image2d/store/object.hpp>

namespace sanguis::tiles
{

SANGUIS_TILES_SYMBOL
sge::image2d::store::object error_image(sanguis::tiles::error);

}

#endif
