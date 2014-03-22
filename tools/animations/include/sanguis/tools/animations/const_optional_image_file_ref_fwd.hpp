#ifndef SANGUIS_TOOLS_ANIMATIONS_CONST_OPTIONAL_IMAGE_FILE_REF_FWD_HPP_INCLUDED
#define SANGUIS_TOOLS_ANIMATIONS_CONST_OPTIONAL_IMAGE_FILE_REF_FWD_HPP_INCLUDED

#include <sge/image2d/file_fwd.hpp>
#include <fcppt/optional_fwd.hpp>


namespace sanguis
{
namespace tools
{
namespace animations
{

typedef
fcppt::optional<
	sge::image2d::file const &
>
const_optional_image_file_ref;

}
}
}

#endif
