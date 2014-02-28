#include <sanguis/model/object.hpp>
#include <sanguis/model/aux_/deserialize/animation_delay.hpp>
#include <sanguis/model/aux_/deserialize/cell_size.hpp>
#include <sanguis/model/aux_/deserialize/image_name.hpp>
#include <sanguis/model/aux_/deserialize/object.hpp>
#include <sanguis/model/aux_/deserialize/part_map.hpp>
#include <sge/parse/json/object_fwd.hpp>


sanguis::model::object
sanguis::model::aux_::deserialize::object(
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
				_object
			),
			sanguis::model::aux_::deserialize::image_name(
				_object
			)
		};
}
