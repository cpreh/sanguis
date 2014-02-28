#include <sanguis/load/model/global_parameters.hpp>
#include <sanguis/load/model/lookup_weapon_name.hpp>
#include <sanguis/load/model/make_weapon_categories.hpp>
#include <sanguis/load/model/weapon_category_map.hpp>
#include <sanguis/load/model/weapon_category.hpp>
#include <sanguis/model/part.hpp>
#include <sanguis/model/weapon_category_map.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/algorithm/map.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


sanguis::load::model::weapon_category_map
sanguis::load::model::make_weapon_categories(
	sanguis::model::part const &_part,
	sanguis::load::model::global_parameters const &_parameters
)
{
	return
		fcppt::algorithm::map<
			sanguis::load::model::weapon_category_map
		>(
			_part.weapon_categories(),
			[
				&_parameters
			](
				sanguis::model::weapon_category_map::value_type const &_weapon_category_pair
			)
			{
				return
					std::make_pair(
						sanguis::load::model::lookup_weapon_name(
							_weapon_category_pair.first
						),
						fcppt::make_unique_ptr<
							sanguis::load::model::weapon_category
						>(
							_weapon_category_pair.second,
							_parameters.new_image(
								_weapon_category_pair.second.image_name()
							)
						)
					);
			}
		);
}
