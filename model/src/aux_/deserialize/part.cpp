#include <sanguis/model/part.hpp>
#include <sanguis/model/aux_/deserialize/image.hpp>
#include <sanguis/model/aux_/deserialize/parameters_fwd.hpp>
#include <sanguis/model/aux_/deserialize/part.hpp>
#include <sanguis/model/aux_/deserialize/weapon_category_map.hpp>
#include <sge/parse/json/object_fwd.hpp>


sanguis::model::part
sanguis::model::aux_::deserialize::part(
	sanguis::model::aux_::deserialize::parameters const &_parameters,
	sge::parse::json::object const &_object
)
{
	return
		sanguis::model::part(
			sanguis::model::aux_::deserialize::weapon_category_map(
				_parameters,
				_object
			),
			sanguis::model::aux_::deserialize::image(
				_parameters,
				_object
			)
		);
}
