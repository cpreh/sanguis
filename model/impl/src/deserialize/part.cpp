#include <sanguis/model/part.hpp>
#include <sanguis/model/impl/deserialize/image_name.hpp>
#include <sanguis/model/impl/deserialize/part.hpp>
#include <sanguis/model/impl/deserialize/weapon_category_map.hpp>
#include <sge/parse/json/object_fwd.hpp>


sanguis::model::part
sanguis::model::impl::deserialize::part(
	sge::parse::json::object const &_object
)
{
	return
		sanguis::model::part(
			sanguis::model::impl::deserialize::weapon_category_map(
				_object
			),
			sanguis::model::impl::deserialize::image_name(
				_object
			)
		);
}
