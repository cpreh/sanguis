#include <sanguis/model/animation.hpp>
#include <sanguis/model/object.hpp>
#include <sanguis/model/optional_image_name.hpp>
#include <sanguis/model/part.hpp>
#include <sanguis/model/weapon_category.hpp>
#include <sanguis/tools/animations/image_file_map.hpp>
#include <sanguis/tools/animations/load_image_files.hpp>
#include <sge/image2d/file.hpp>
#include <sge/image2d/system.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/filesystem/path.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


sanguis::tools::animations::image_file_map
sanguis::tools::animations::load_image_files(
	sge::image2d::system &_image_system,
	boost::filesystem::path const &_path,
	sanguis::model::object const &_model
)
{
	sanguis::tools::animations::image_file_map result;

	auto const load_image(
		[
			&_image_system,
			&_path,
			&result
		](
			sanguis::model::optional_image_name const &_name
		)
		{
			if(
				!_name
			)
				return;

			auto const it(
				result.find(
					*_name
				)
			);

			if(
				it
				!=
				result.end()
			)
				return;

			result.insert(
				std::make_pair(
					*_name,
					_image_system.load(
						_path
						/
						_name->get()
					)
				)
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
		std::move(
			result
		);
}
