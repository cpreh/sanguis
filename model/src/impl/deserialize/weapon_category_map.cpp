#include <sanguis/model/weapon_category_map.hpp>
#include <sanguis/model/impl/deserialize/map.hpp>
#include <sanguis/model/impl/deserialize/weapon_category.hpp>
#include <sanguis/model/impl/deserialize/weapon_category_map.hpp>
#include <sge/parse/json/object_fwd.hpp>
#include <fcppt/text.hpp>


sanguis::model::weapon_category_map
sanguis::model::impl::deserialize::weapon_category_map(
	sge::parse::json::object const &_object
)
{
	return
		sanguis::model::impl::deserialize::map<
			sanguis::model::weapon_category_map
		>(
			_object,
			FCPPT_TEXT("weapon_categories"),
			&sanguis::model::impl::deserialize::weapon_category
		);
}
