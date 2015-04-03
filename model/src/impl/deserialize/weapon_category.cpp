#include <sanguis/model/weapon_category.hpp>
#include <sanguis/model/impl/deserialize/animation_map.hpp>
#include <sanguis/model/impl/deserialize/image_name.hpp>
#include <sanguis/model/impl/deserialize/weapon_category.hpp>
#include <sge/parse/json/object_fwd.hpp>


sanguis::model::weapon_category
sanguis::model::impl::deserialize::weapon_category(
	sge::parse::json::object const &_object
)
{
	return
		sanguis::model::weapon_category(
			sanguis::model::impl::deserialize::animation_map(
				_object
			),
			sanguis::model::impl::deserialize::image_name(
				_object
			)
		);
}
