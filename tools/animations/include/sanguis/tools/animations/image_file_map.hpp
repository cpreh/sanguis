#ifndef SANGUIS_TOOLS_ANIMATIONS_IMAGE_FILE_MAP_HPP_INCLUDED
#define SANGUIS_TOOLS_ANIMATIONS_IMAGE_FILE_MAP_HPP_INCLUDED

#include <sanguis/model/image_name.hpp>
#include <fcppt/config/external_begin.hpp>
#include <QImage>
#include <unordered_map>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace tools
{
namespace animations
{

typedef
std::unordered_map<
	sanguis::model::image_name,
	QImage
>
image_file_map;

}
}
}

#endif
