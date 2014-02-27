#ifndef SANGUIS_MODEL_OPTIONAL_IMAGE_FWD_HPP_INCLUDED
#define SANGUIS_MODEL_OPTIONAL_IMAGE_FWD_HPP_INCLUDED

#include <sge/image2d/file_unique_ptr.hpp>
#include <fcppt/optional_fwd.hpp>


namespace sanguis
{
namespace model
{

typedef
fcppt::optional<
	sge::image2d::file_unique_ptr
>
optional_image;

}
}

#endif
