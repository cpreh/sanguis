#include <sanguis/model/object.hpp>
#include <sanguis/model/impl/serialize/animation_delay.hpp>
#include <sanguis/model/impl/serialize/cell_size.hpp>
#include <sanguis/model/impl/serialize/image_name.hpp>
#include <sanguis/model/impl/serialize/object.hpp>
#include <sanguis/model/impl/serialize/part_map.hpp>
#include <sge/parse/json/member.hpp>
#include <sge/parse/json/member_map.hpp>
#include <sge/parse/json/object.hpp>
#include <sge/parse/json/value.hpp>
#include <fcppt/optional/cat.hpp>
#include <fcppt/optional/object_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <array>
#include <fcppt/config/external_end.hpp>


sge::parse::json::object
sanguis::model::impl::serialize::object(
	sanguis::model::object const &_object
)
{
	return
		sge::parse::json::object(
			fcppt::optional::cat<
				sge::parse::json::member_map
			>(
				std::array<
					fcppt::optional::object<
						sge::parse::json::member
					>,
					4
				>{{
					fcppt::optional::object<
						sge::parse::json::member
					>{
						sanguis::model::impl::serialize::cell_size(
							_object.cell_size()
						)
					},
					sanguis::model::impl::serialize::animation_delay(
						_object.animation_delay()
					),
					fcppt::optional::object<
						sge::parse::json::member
					>{
						sanguis::model::impl::serialize::part_map(
							_object.parts()
						)
					},
					sanguis::model::impl::serialize::image_name(
						_object.image_name()
					)
				}}
			)
		);
}
