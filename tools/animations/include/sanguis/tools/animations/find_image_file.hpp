#ifndef SANGUIS_TOOLS_ANIMATIONS_FIND_IMAGE_FILE_HPP_INCLUDED
#define SANGUIS_TOOLS_ANIMATIONS_FIND_IMAGE_FILE_HPP_INCLUDED

#include <sanguis/model/object_fwd.hpp>
#include <sanguis/tools/animations/const_optional_image_file_ref.hpp>
#include <sanguis/tools/animations/image_file_map.hpp>
#include <fcppt/string.hpp>


namespace sanguis
{
namespace tools
{
namespace animations
{

sanguis::tools::animations::const_optional_image_file_ref const
find_image_file(
	sanguis::tools::animations::image_file_map const &,
	sanguis::model::object const &,
	// TODO: Better interface
	fcppt::string const &,
	fcppt::string const &,
	fcppt::string const &
);

}
}
}

#endif
