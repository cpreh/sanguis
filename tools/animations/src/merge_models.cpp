#include <sanguis/model/animation.hpp>
#include <sanguis/model/animation_map.hpp>
#include <sanguis/model/object.hpp>
#include <sanguis/model/part_map.hpp>
#include <sanguis/model/weapon_category_map.hpp>
#include <sanguis/tools/animations/get_or_default_animation.hpp>
#include <sanguis/tools/animations/merge_models.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


sanguis::model::object
sanguis::tools::animations::merge_models(
	sanguis::model::object const &_previous_model,
	sanguis::model::object &&_new_model
)
{
	_new_model.animation_delay(
		_previous_model.animation_delay()
	);

	for(
		sanguis::model::part_map::value_type &part
		:
		_new_model.parts()
	)
		for(
			sanguis::model::weapon_category_map::value_type &weapon_category
			:
			part.second.weapon_categories()
		)
			for(
				sanguis::model::animation_map::value_type &animation
				:
				weapon_category.second.animations()
			)
			{
				sanguis::model::animation const previous_animation(
					sanguis::tools::animations::get_or_default_animation(
						_previous_model,
						part.first,
						weapon_category.first,
						animation.first
					)
				);

				animation.second.animation_delay(
					previous_animation.animation_delay()
				);

				animation.second.animation_sound(
					previous_animation.animation_sound()
				);
			}

	return
		std::move(
			_new_model
		);
}
