#include <sanguis/model/animation_map.hpp>
#include <sanguis/model/aux_/serialize/animation.hpp>
#include <sanguis/model/aux_/serialize/animation_map.hpp>
#include <sanguis/model/aux_/serialize/map.hpp>
#include <sge/parse/json/member.hpp>
#include <fcppt/text.hpp>


sge::parse::json::member
sanguis::model::aux_::serialize::animation_map(
	sanguis::model::animation_map const &_animations
)
{
	return
		sanguis::model::aux_::serialize::map(
			_animations,
			FCPPT_TEXT("animations"),
			&sanguis::model::aux_::serialize::animation
		);
}
