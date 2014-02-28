#include <sanguis/load/model/animation.hpp>
#include <sanguis/load/model/animation_map.hpp>
#include <sanguis/load/model/global_parameters.hpp>
#include <sanguis/load/model/make_animations.hpp>
#include <sanguis/load/model/lookup_animation_name.hpp>
#include <sanguis/model/animation_map.hpp>
#include <sanguis/model/weapon_category.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/algorithm/map.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


sanguis::load::model::animation_map
sanguis::load::model::make_animations(
	sanguis::model::weapon_category const &_weapon_category,
	sanguis::load::model::global_parameters const &_parameters
)
{
	return
		fcppt::algorithm::map<
			sanguis::load::model::animation_map
		>(
			_weapon_category.animations(),
			[
				&_parameters
			](
				sanguis::model::animation_map::value_type const &_animation_pair
			)
			{
				return
					std::make_pair(
						sanguis::load::model::lookup_animation_name(
							_animation_pair.first
						),
						fcppt::make_unique_ptr<
							sanguis::load::model::animation
						>(
							_animation_pair.second,
							_parameters.new_image(
								_animation_pair.second.image_name()
							)
						)
					);
			}
		);
}
