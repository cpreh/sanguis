#include <sanguis/model/part.hpp>
#include <sanguis/model/impl/serialize/image_name.hpp>
#include <sanguis/model/impl/serialize/part.hpp>
#include <sanguis/model/impl/serialize/weapon_category_map.hpp>
#include <sge/parse/json/member_map.hpp>
#include <sge/parse/json/object.hpp>
#include <sge/parse/json/optional_member.hpp>
#include <fcppt/optional/cat.hpp>
#include <fcppt/config/external_begin.hpp>
#include <array>
#include <fcppt/config/external_end.hpp>


sge::parse::json::object
sanguis::model::impl::serialize::part(
	sanguis::model::part const &_part
)
{
	return
		sge::parse::json::object(
			fcppt::optional::cat<
				sge::parse::json::member_map
			>(
				std::array<
					sge::parse::json::optional_member,
					2
				>{{
					sge::parse::json::optional_member{
						sanguis::model::impl::serialize::weapon_category_map(
							_part.weapon_categories()
						)
					},
					sanguis::model::impl::serialize::image_name(
						_part.image_name()
					)
				}}
			)
		);
}
