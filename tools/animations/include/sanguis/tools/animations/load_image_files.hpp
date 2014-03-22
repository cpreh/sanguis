#ifndef SANGUIS_TOOLS_ANIMATIONS_LOAD_IMAGE_FILES_HPP_INCLUDED
#define SANGUIS_TOOLS_ANIMATIONS_LOAD_IMAGE_FILES_HPP_INCLUDED

#include <sanguis/model/object_fwd.hpp>
#include <sanguis/tools/animations/image_file_map.hpp>
#include <sge/image2d/system_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/filesystem/path.hpp>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace tools
{
namespace animations
{

sanguis::tools::animations::image_file_map
load_image_files(
	sge::image2d::system &,
	boost::filesystem::path const &,
	sanguis::model::object const &
);

}
}
}

#endif
