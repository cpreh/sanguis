#include <sanguis/model/animation.hpp>
#include <sanguis/model/impl/serialize/animation.hpp>
#include <sanguis/model/impl/serialize/animation_delay.hpp>
#include <sanguis/model/impl/serialize/animation_range.hpp>
#include <sanguis/model/impl/serialize/animation_sound.hpp>
#include <sanguis/model/impl/serialize/image_name.hpp>
#include <sge/parse/json/member_map.hpp>
#include <sge/parse/json/object.hpp>
#include <sge/parse/json/optional_member.hpp>
#include <fcppt/algorithm/join.hpp>
#include <fcppt/optional/cat.hpp>
#include <fcppt/config/external_begin.hpp>
#include <array>
#include <fcppt/config/external_end.hpp>


sge::parse::json::object
sanguis::model::impl::serialize::animation(
	sanguis::model::animation const &_animation
)
{
	return
		sge::parse::json::object(
			fcppt::optional::cat<
				sge::parse::json::member_map
			>(
				std::array<
					sge::parse::json::optional_member,
					4
				>{{
					sge::parse::json::optional_member{
						sanguis::model::impl::serialize::animation_range(
							_animation.animation_range()
						)
					},
					sanguis::model::impl::serialize::animation_delay(
						_animation.animation_delay()
					),
					sanguis::model::impl::serialize::animation_sound(
						_animation.animation_sound()
					),
					sanguis::model::impl::serialize::image_name(
						_animation.image_name()
					)
				}}
			)
		);
}
