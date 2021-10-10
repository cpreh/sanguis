#ifndef SANGUIS_TOOLS_ANIMATIONS_IMAGE_FILE_MAP_HPP_INCLUDED
#define SANGUIS_TOOLS_ANIMATIONS_IMAGE_FILE_MAP_HPP_INCLUDED

#include <sanguis/model/image_name.hpp>
#include <fcppt/config/external_begin.hpp>
#include <QImage>
#include <unordered_map>
#include <fcppt/config/external_end.hpp>

namespace sanguis::tools::animations
{

using image_file_map = std::unordered_map<sanguis::model::image_name, QImage>;

}

#endif
