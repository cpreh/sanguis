#ifndef SANGUIS_TOOLS_ANIMATIONS_LOAD_IMAGE_FILES_HPP_INCLUDED
#define SANGUIS_TOOLS_ANIMATIONS_LOAD_IMAGE_FILES_HPP_INCLUDED

#include <sanguis/model/object_fwd.hpp>
#include <sanguis/tools/animations/image_file_map.hpp>
#include <fcppt/config/external_begin.hpp>
#include <filesystem>
#include <fcppt/config/external_end.hpp>

namespace sanguis::tools::animations
{

sanguis::tools::animations::image_file_map
load_image_files(std::filesystem::path const &, sanguis::model::object const &);

}

#endif
