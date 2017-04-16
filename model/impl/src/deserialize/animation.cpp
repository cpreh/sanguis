#include <sanguis/model/animation.hpp>
#include <sanguis/model/impl/deserialize/animation.hpp>
#include <sanguis/model/impl/deserialize/animation_delay.hpp>
#include <sanguis/model/impl/deserialize/animation_range.hpp>
#include <sanguis/model/impl/deserialize/animation_sound.hpp>
#include <sanguis/model/impl/deserialize/image_name.hpp>
#include <sanguis/model/impl/deserialize/weapon_category_map.hpp>
#include <sge/parse/json/object_fwd.hpp>


sanguis::model::animation
sanguis::model::impl::deserialize::animation(
	sge::parse::json::object const &_object
)
{
	return
		sanguis::model::animation(
			sanguis::model::impl::deserialize::animation_range(
				_object
			),
			sanguis::model::impl::deserialize::animation_delay(
				_object
			),
			sanguis::model::impl::deserialize::animation_sound(
				_object
			),
			sanguis::model::impl::deserialize::image_name(
				_object
			)
		);
}
