#include <sanguis/model/animation.hpp>
#include <sanguis/model/impl/serialize/animation.hpp>
#include <sanguis/model/impl/serialize/animation_delay.hpp>
#include <sanguis/model/impl/serialize/animation_range.hpp>
#include <sanguis/model/impl/serialize/animation_sound.hpp>
#include <sanguis/model/impl/serialize/image_name.hpp>
#include <sge/parse/json/member_map.hpp>
#include <sge/parse/json/object.hpp>
#include <fcppt/assign/make_container_opt.hpp>


sge::parse::json::object
sanguis::model::impl::serialize::animation(
	sanguis::model::animation const &_animation
)
{
	return
		sge::parse::json::object(
			fcppt::assign::make_container_opt<
				sge::parse::json::member_map
			>(
				sanguis::model::impl::serialize::animation_range(
					_animation.animation_range()
				),
				sanguis::model::impl::serialize::animation_delay(
					_animation.animation_delay()
				),
				sanguis::model::impl::serialize::animation_sound(
					_animation.animation_sound()
				),
				sanguis::model::impl::serialize::image_name(
					_animation.image_name()
				)
			)
		);
}
