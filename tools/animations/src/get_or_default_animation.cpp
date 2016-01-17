#include <sanguis/model/animation.hpp>
#include <sanguis/model/animation_name.hpp>
#include <sanguis/model/animation_range.hpp>
#include <sanguis/model/object.hpp>
#include <sanguis/model/optional_animation_delay.hpp>
#include <sanguis/model/optional_animation_sound.hpp>
#include <sanguis/model/optional_image_name.hpp>
#include <sanguis/model/part_name.hpp>
#include <sanguis/model/weapon_category_name.hpp>
#include <sanguis/tools/animations/get_or_default_animation.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/container/find_opt_mapped.hpp>
#include <fcppt/optional/bind.hpp>
#include <fcppt/optional/copy_value.hpp>
#include <fcppt/optional/from.hpp>


sanguis::model::animation
sanguis::tools::animations::get_or_default_animation(
	sanguis::model::object const &_model,
	sanguis::model::part_name const &_part_name,
	sanguis::model::weapon_category_name const &_weapon_category_name,
	sanguis::model::animation_name const &_animation_name
)
{
	return
		fcppt::optional::from(
			fcppt::optional::bind(
				fcppt::container::find_opt_mapped(
					_model.parts(),
					_part_name
				),
				[
					&_weapon_category_name,
					&_animation_name
				](
					fcppt::reference<
						sanguis::model::part const
					> const _part
				)
				{
					return
						fcppt::optional::copy_value(
							fcppt::optional::bind(
								fcppt::container::find_opt_mapped(
									_part.get().weapon_categories(),
									_weapon_category_name
								),
								[
									&_animation_name
								](
									fcppt::reference<
										sanguis::model::weapon_category const
									> const _weapon_category
								)
								{
									return
										fcppt::container::find_opt_mapped(
											_weapon_category.get().animations(),
											_animation_name
										);
								}
							)
						);
				}
			),
			[]{
				return
					sanguis::model::animation(
						sanguis::model::animation_range(
							0u,
							1u
						),
						sanguis::model::optional_animation_delay(),
						sanguis::model::optional_animation_sound(),
						sanguis::model::optional_image_name()
					);
			}
		);
}
