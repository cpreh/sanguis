#include <sanguis/model/animation_map.hpp>
#include <sanguis/model/impl/serialize/animation.hpp>
#include <sanguis/model/impl/serialize/animation_map.hpp>
#include <sanguis/model/impl/serialize/map.hpp>
#include <sge/parse/json/member.hpp>
#include <fcppt/text.hpp>


sge::parse::json::member
sanguis::model::impl::serialize::animation_map(
	sanguis::model::animation_map const &_animations
)
{
	return
		sanguis::model::impl::serialize::map(
			_animations,
			FCPPT_TEXT("animations"),
			&sanguis::model::impl::serialize::animation
		);
}
