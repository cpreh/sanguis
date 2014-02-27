#include <sanguis/model/object.hpp>
#include <sanguis/model/aux_/deserialize/animation_delay.hpp>
#include <sanguis/model/aux_/deserialize/cell_size.hpp>
#include <sanguis/model/aux_/deserialize/image.hpp>
#include <sanguis/model/aux_/deserialize/object.hpp>
#include <sanguis/model/aux_/deserialize/parameters_fwd.hpp>
#include <sanguis/model/aux_/deserialize/part_map.hpp>
#include <sge/parse/json/object_fwd.hpp>


sanguis::model::object
sanguis::model::aux_::deserialize::object(
	sanguis::model::aux_::deserialize::parameters const &_parameters,
	sge::parse::json::object const &_object
)
{
	return
		sanguis::model::object{
			sanguis::model::aux_::deserialize::cell_size(
				_object
			),
			sanguis::model::aux_::deserialize::animation_delay(
				_object
			),
			sanguis::model::aux_::deserialize::part_map(
				_parameters,
				_object
			),
			sanguis::model::aux_::deserialize::image(
				_parameters,
				_object
			)
		};
}
