#include "base_animation_not_found.hpp"
#include <sge/text.hpp>

sanguis::load::model::base_animation_not_found::base_animation_not_found(
	animation_type::type const anim_type_)
:
	exception(
		SGE_TEXT("base animation not found!")),
	anim_type_(anim_type_)
{}

sanguis::animation_type::type
sanguis::load::model::base_animation_not_found::anim_type() const
{
	return anim_type_;
}
