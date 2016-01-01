#include <sanguis/model/animation.hpp>
#include <sanguis/model/image_name.hpp>
#include <sanguis/model/object.hpp>
#include <sanguis/model/optional_image_name.hpp>
#include <sanguis/model/part.hpp>
#include <sanguis/model/weapon_category.hpp>
#include <sanguis/tools/animations/image_file_map.hpp>
#include <sanguis/tools/animations/load_image_files.hpp>
#include <sanguis/tools/animations/qtutil/from_fcppt_string.hpp>
#include <fcppt/container/find_opt.hpp>
#include <fcppt/filesystem/path_to_string.hpp>
#include <fcppt/optional/maybe_void.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/filesystem/path.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


sanguis::tools::animations::image_file_map
sanguis::tools::animations::load_image_files(
	boost::filesystem::path const &_path,
	sanguis::model::object const &_model
)
{
	sanguis::tools::animations::image_file_map result;

	auto const load_image(
		[
			&_path,
			&result
		](
			sanguis::model::optional_image_name const &_opt_name
		)
		{
			fcppt::optional::maybe_void(
				_opt_name,
				[
					&_path,
					&result
				](
					sanguis::model::image_name const &_name
				)
				{
					if(
						fcppt::container::find_opt(
							result,
							_name
						).has_value()
					)
						return;

					QImage image(
						sanguis::tools::animations::qtutil::from_fcppt_string(
							fcppt::filesystem::path_to_string(
								_path
								/
								_name.get()
							)
						)
					);

					// TODO
					if(
						image.isNull()
					)
						return;

					result.insert(
						std::make_pair(
							_name,
							std::move(
								image
							)
						)
					);
				}
			);
		}
	);

	load_image(
		_model.image_name()
	);

	for(
		auto const &part
		:
		_model.parts()
	)
	{
		load_image(
			part.second.image_name()
		);

		for(
			auto const &weapon
			:
			part.second.weapon_categories()
		)
		{
			load_image(
				weapon.second.image_name()
			);

			for(
				auto const &animation
				:
				weapon.second.animations()
			)
				load_image(
					animation.second.image_name()
				);
		}
	}

	return
		result;
}
