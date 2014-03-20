#include <sanguis/model/object.hpp>
#include <sanguis/model/aux_/serialize/animation_delay.hpp>
#include <sanguis/model/aux_/serialize/cell_size.hpp>
#include <sanguis/model/aux_/serialize/image_name.hpp>
#include <sanguis/model/aux_/serialize/object.hpp>
#include <sanguis/model/aux_/serialize/part_map.hpp>
#include <sge/parse/json/member_map.hpp>
#include <sge/parse/json/object.hpp>
#include <fcppt/assign/make_container_opt.hpp>


sge::parse::json::object
sanguis::model::aux_::serialize::object(
	sanguis::model::object const &_object
)
{
	return
		sge::parse::json::object(
			fcppt::assign::make_container_opt<
				sge::parse::json::member_map
			>(
				sanguis::model::aux_::serialize::cell_size(
					_object.cell_size()
				),
				sanguis::model::aux_::serialize::animation_delay(
					_object.animation_delay()
				),
				sanguis::model::aux_::serialize::part_map(
					_object.parts()
				),
				sanguis::model::aux_::serialize::image_name(
					_object.image_name()
				)
			)
		);
}
