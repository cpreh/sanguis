#include <sanguis/model/animation_map.hpp>
#include <sanguis/model/impl/serialize/animation.hpp>
#include <sanguis/model/impl/serialize/animation_map.hpp>
#include <sanguis/model/impl/serialize/map.hpp>
#include <sge/charconv/utf8_string.hpp>
#include <sge/parse/json/member.hpp>


sge::parse::json::member
sanguis::model::impl::serialize::animation_map(
	sanguis::model::animation_map const &_animations
)
{
	return
		sanguis::model::impl::serialize::map(
			_animations,
			sge::charconv::utf8_string{
				"animations"
			},
			&sanguis::model::impl::serialize::animation
		);
}
