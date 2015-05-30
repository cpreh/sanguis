#ifndef SANGUIS_TILES_IMPL_ERROR_IMAGE_HPP_INCLUDED
#define SANGUIS_TILES_IMPL_ERROR_IMAGE_HPP_INCLUDED

#include <sanguis/tiles/impl/error_image_color_pair_fwd.hpp>
#include <sge/image2d/store/object.hpp>


namespace sanguis
{
namespace tiles
{
namespace impl
{

sge::image2d::store::object
error_image(
	sanguis::tiles::impl::error_image_color_pair
);

}
}
}

#endif
