#include <sanguis/model/weapon_category.hpp>
#include <sanguis/model/aux_/deserialize/animation_map.hpp>
#include <sanguis/model/aux_/deserialize/image.hpp>
#include <sanguis/model/aux_/deserialize/parameters_fwd.hpp>
#include <sanguis/model/aux_/deserialize/weapon_category.hpp>
#include <sge/parse/json/object_fwd.hpp>


sanguis::model::weapon_category
sanguis::model::aux_::deserialize::weapon_category(
	sanguis::model::aux_::deserialize::parameters const &_parameters,
	sge::parse::json::object const &_object
)
{
	return
		sanguis::model::weapon_category(
			sanguis::model::aux_::deserialize::animation_map(
				_parameters,
				_object
			),
			sanguis::model::aux_::deserialize::image(
				_parameters,
				_object
			)
		);
}
