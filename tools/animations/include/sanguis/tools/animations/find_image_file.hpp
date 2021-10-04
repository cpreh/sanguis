#ifndef SANGUIS_TOOLS_ANIMATIONS_FIND_IMAGE_FILE_HPP_INCLUDED
#define SANGUIS_TOOLS_ANIMATIONS_FIND_IMAGE_FILE_HPP_INCLUDED

#include <sanguis/model/animation_name_fwd.hpp>
#include <sanguis/model/object_fwd.hpp>
#include <sanguis/model/part_name_fwd.hpp>
#include <sanguis/model/weapon_category_name_fwd.hpp>
#include <sanguis/tools/animations/const_optional_image_file_ref.hpp>
#include <sanguis/tools/animations/image_file_map.hpp>


namespace sanguis::tools::animations
{

sanguis::tools::animations::const_optional_image_file_ref
find_image_file(
	sanguis::tools::animations::image_file_map const &,
	sanguis::model::object const &,
	sanguis::model::part_name const &,
	sanguis::model::weapon_category_name const &,
	sanguis::model::animation_name const &
);

}

#endif
