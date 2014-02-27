#include <sanguis/model/weapon_category_map.hpp>
#include <sanguis/model/aux_/deserialize/map.hpp>
#include <sanguis/model/aux_/deserialize/parameters_fwd.hpp>
#include <sanguis/model/aux_/deserialize/weapon_category.hpp>
#include <sanguis/model/aux_/deserialize/weapon_category_map.hpp>
#include <sge/parse/json/object_fwd.hpp>
#include <fcppt/text.hpp>


sanguis::model::weapon_category_map
sanguis::model::aux_::deserialize::weapon_category_map(
	sanguis::model::aux_::deserialize::parameters const &_parameters,
	sge::parse::json::object const &_object
)
{
	return
		sanguis::model::aux_::deserialize::map<
			sanguis::model::weapon_category_map
		>(
			_parameters,
			_object,
			FCPPT_TEXT("weapon_categories"),
			&sanguis::model::aux_::deserialize::weapon_category
		);
}
