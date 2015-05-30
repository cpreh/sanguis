#ifndef SANGUIS_TILES_ERROR_IMAGE_ARRAY_FWD_HPP_INCLUDED
#define SANGUIS_TILES_ERROR_IMAGE_ARRAY_FWD_HPP_INCLUDED

#include <sanguis/tiles/error_fwd.hpp>
#include <sge/image2d/store/object_fwd.hpp>
#include <fcppt/container/enum_array_fwd.hpp>


namespace sanguis
{
namespace tiles
{

typedef
fcppt::container::enum_array<
	sanguis::tiles::error,
	sge::image2d::store::object
>
error_image_array;

}
}

#endif
