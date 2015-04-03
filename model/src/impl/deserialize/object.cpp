#include <sanguis/model/object.hpp>
#include <sanguis/model/impl/deserialize/animation_delay.hpp>
#include <sanguis/model/impl/deserialize/cell_size.hpp>
#include <sanguis/model/impl/deserialize/image_name.hpp>
#include <sanguis/model/impl/deserialize/object.hpp>
#include <sanguis/model/impl/deserialize/part_map.hpp>
#include <sge/parse/json/object_fwd.hpp>


sanguis::model::object
sanguis::model::impl::deserialize::object(
	sge::parse::json::object const &_object
)
{
	return
		sanguis::model::object{
			sanguis::model::impl::deserialize::cell_size(
				_object
			),
			sanguis::model::impl::deserialize::animation_delay(
				_object
			),
			sanguis::model::impl::deserialize::part_map(
				_object
			),
			sanguis::model::impl::deserialize::image_name(
				_object
			)
		};
}
