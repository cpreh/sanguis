#include <sanguis/animation_type.hpp>
#include <sanguis/exception.hpp>
#include <sanguis/load/model/base_animation_not_found.hpp>
#include <fcppt/text.hpp>


sanguis::load::model::base_animation_not_found::base_animation_not_found(
	sanguis::animation_type const _anim_type
)
:
	sanguis::exception(
		FCPPT_TEXT("base animation not found!")
	),
	anim_type_(
		_anim_type
	)
{
}

sanguis::animation_type
sanguis::load::model::base_animation_not_found::anim_type() const
{
	return anim_type_;
}
