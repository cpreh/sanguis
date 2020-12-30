#include <sanguis/model/weapon_category.hpp>
#include <sanguis/model/impl/serialize/animation_map.hpp>
#include <sanguis/model/impl/serialize/image_name.hpp>
#include <sanguis/model/impl/serialize/weapon_category.hpp>
#include <sge/parse/json/member.hpp>
#include <sge/parse/json/member_map.hpp>
#include <sge/parse/json/object.hpp>
#include <sge/parse/json/value.hpp>
#include <fcppt/array/object_impl.hpp>
#include <fcppt/optional/cat.hpp>
#include <fcppt/optional/object_impl.hpp>


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
				fcppt::array::object<
					fcppt::optional::object<
						sge::parse::json::member
					>,
					2
				>{
					fcppt::optional::object<
						sge::parse::json::member
					>{
						sanguis::model::impl::serialize::animation_map(
							_weapon_category.animations()
						)
					},
					sanguis::model::impl::serialize::image_name(
						_weapon_category.image_name()
					)
				}
			)
		);
}
