#ifndef SANGUIS_TILES_IMPL_ERROR_IMAGE_COLOR_PAIR_FWD_HPP_INCLUDED
#define SANGUIS_TILES_IMPL_ERROR_IMAGE_COLOR_PAIR_FWD_HPP_INCLUDED

#include <sge/image/color/any/object_fwd.hpp>
#include <fcppt/tuple/object_fwd.hpp>


namespace sanguis
{
namespace tiles
{
namespace impl
{

using
error_image_color_pair
=
fcppt::tuple::object<
	sge::image::color::any::object,
	sge::image::color::any::object
>;

}
}
}

#endif
