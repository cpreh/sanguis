#include <sanguis/model/animation.hpp>
#include <sanguis/model/animation_name.hpp>
#include <sanguis/model/image_name.hpp>
#include <sanguis/model/object.hpp>
#include <sanguis/model/optional_image_name.hpp>
#include <sanguis/model/part.hpp>
#include <sanguis/model/part_name.hpp>
#include <sanguis/model/weapon_category.hpp>
#include <sanguis/model/weapon_category_name.hpp>
#include <sanguis/tools/animations/const_optional_image_file_ref.hpp>
#include <sanguis/tools/animations/find_image_file.hpp>
#include <sanguis/tools/animations/image_file_map.hpp>
#include <fcppt/reference_wrapper_impl.hpp>
#include <fcppt/container/find_opt_mapped.hpp>
#include <fcppt/optional/maybe_void.hpp>
#include <fcppt/config/external_begin.hpp>
#include <QImage>
#include <fcppt/config/external_end.hpp>


sanguis::tools::animations::const_optional_image_file_ref
sanguis::tools::animations::find_image_file(
	sanguis::tools::animations::image_file_map const &_image_files,
	sanguis::model::object const &_model,
	sanguis::model::part_name const &_part_name,
	sanguis::model::weapon_category_name const &_weapon_name,
	sanguis::model::animation_name const &_animation_name
)
{
	sanguis::tools::animations::const_optional_image_file_ref result;

	auto const update_result(
		[
			&result,
			&_image_files
		](
			sanguis::model::optional_image_name const &_opt_image_name
		)
		{
			fcppt::optional::maybe_void(
				_opt_image_name,
				[
					&result,
					&_image_files
				](
					sanguis::model::image_name const &_image_name
				)
				{
					fcppt::optional::maybe_void(
						fcppt::container::find_opt_mapped(
							_image_files,
							_image_name
						),
						[
							&result
						](
							fcppt::reference_wrapper<
								QImage const
							> const _image
						)
						{
							result =
								sanguis::tools::animations::const_optional_image_file_ref(
									_image
								);
						}
					);
				}
			);
		}
	);

	update_result(
		_model.image_name()
	);

	sanguis::model::part const &part(
		_model.part(
			_part_name
		)
	);

	update_result(
		part.image_name()
	);

	sanguis::model::weapon_category const &weapon(
		part.weapon_category(
			_weapon_name
		)
	);

	update_result(
		weapon.image_name()
	);

	update_result(
		weapon.animation(
			_animation_name
		).image_name()
	);

	return
		result;
}
