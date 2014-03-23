#include <sanguis/model/animation.hpp>
#include <sanguis/model/object.hpp>
#include <sanguis/model/optional_image_name.hpp>
#include <sanguis/model/part.hpp>
#include <sanguis/model/weapon_category.hpp>
#include <sanguis/tools/animations/const_optional_image_file_ref.hpp>
#include <sanguis/tools/animations/find_image_file.hpp>
#include <sanguis/tools/animations/image_file_map.hpp>
#include <fcppt/string.hpp>


sanguis::tools::animations::const_optional_image_file_ref const
sanguis::tools::animations::find_image_file(
	sanguis::tools::animations::image_file_map const &_image_files,
	sanguis::model::object const &_model,
	fcppt::string const &_part_name,
	fcppt::string const &_weapon_name,
	fcppt::string const &_animation_name
)
{
	sanguis::tools::animations::const_optional_image_file_ref result;

	auto const update_result(
		[
			&result,
			&_image_files
		](
			sanguis::model::optional_image_name const &_image_name
		)
		{
			if(
				!_image_name
			)
				return;

			auto const it(
				_image_files.find(
					*_image_name
				)
			);

			if(
				it
				!=
				_image_files.end()
			)
				result =
					sanguis::tools::animations::const_optional_image_file_ref(
						it->second
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
