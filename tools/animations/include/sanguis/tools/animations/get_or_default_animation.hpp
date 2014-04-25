#ifndef SANGUIS_TOOLS_ANIMATIONS_GET_OR_DEFAULT_ANIMATION_HPP_INCLUDED
#define SANGUIS_TOOLS_ANIMATIONS_GET_OR_DEFAULT_ANIMATION_HPP_INCLUDED

#include <sanguis/model/animation.hpp>
#include <sanguis/model/animation_name_fwd.hpp>
#include <sanguis/model/object_fwd.hpp>
#include <sanguis/model/part_name_fwd.hpp>
#include <sanguis/model/weapon_category_name_fwd.hpp>


namespace sanguis
{
namespace tools
{
namespace animations
{

sanguis::model::animation
get_or_default_animation(
	sanguis::model::object const &,
	sanguis::model::part_name const &,
	sanguis::model::weapon_category_name const &,
	sanguis::model::animation_name const &
);

}
}
}

#endif
