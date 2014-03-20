#include <sanguis/model/weapon_category.hpp>
#include <sanguis/model/aux_/serialize/animation_map.hpp>
#include <sanguis/model/aux_/serialize/image_name.hpp>
#include <sanguis/model/aux_/serialize/weapon_category.hpp>
#include <sge/parse/json/member_map.hpp>
#include <sge/parse/json/object.hpp>
#include <fcppt/assign/make_container_opt.hpp>


sge::parse::json::object
sanguis::model::aux_::serialize::weapon_category(
	sanguis::model::weapon_category const &_weapon_category
)
{
	return
		sge::parse::json::object(
			fcppt::assign::make_container_opt<
				sge::parse::json::member_map
			>(
				sanguis::model::aux_::serialize::animation_map(
					_weapon_category.animations()
				),
				sanguis::model::aux_::serialize::image_name(
					_weapon_category.image_name()
				)
			)
		);
}
