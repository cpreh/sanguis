#include <sanguis/model/weapon_category.hpp>
#include <sanguis/model/impl/serialize/animation_map.hpp>
#include <sanguis/model/impl/serialize/image_name.hpp>
#include <sanguis/model/impl/serialize/weapon_category.hpp>
#include <sge/parse/json/member_map.hpp>
#include <sge/parse/json/object.hpp>
#include <sge/parse/json/optional_member.hpp>
#include <fcppt/optional/cat.hpp>
#include <fcppt/config/external_begin.hpp>
#include <array>
#include <fcppt/config/external_end.hpp>


sge::parse::json::object
sanguis::model::impl::serialize::weapon_category(
	sanguis::model::weapon_category const &_weapon_category
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
						sanguis::model::impl::serialize::animation_map(
							_weapon_category.animations()
						)
					},
					sanguis::model::impl::serialize::image_name(
						_weapon_category.image_name()
					)
				}}
			)
		);
}
