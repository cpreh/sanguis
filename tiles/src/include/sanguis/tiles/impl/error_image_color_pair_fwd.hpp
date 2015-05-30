#ifndef SANGUIS_TILES_IMPL_ERROR_IMAGE_COLOR_PAIR_FWD_HPP_INCLUDED
#define SANGUIS_TILES_IMPL_ERROR_IMAGE_COLOR_PAIR_FWD_HPP_INCLUDED

#include <sge/image/color/any/object_fwd.hpp>
#include <fcppt/homogenous_pair_fwd.hpp>


namespace sanguis
{
namespace tiles
{
namespace impl
{

typedef
fcppt::homogenous_pair<
	sge::image::color::any::object
>
error_image_color_pair;

}
}
}

#endif
