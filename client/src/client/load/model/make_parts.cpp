#include <sanguis/client/load/model/global_parameters.hpp>
#include <sanguis/client/load/model/make_parts.hpp>
#include <sanguis/client/load/model/part.hpp>
#include <sanguis/client/load/model/part_map.hpp>
#include <sanguis/client/load/model/part_result.hpp>
#include <sanguis/client/load/resource/context.hpp>
#include <sanguis/load/model/path_to_json_file.hpp>
#include <sanguis/model/deserialize.hpp>
#include <sanguis/model/object.hpp>
#include <sanguis/model/part_map.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/algorithm/map.hpp>
#include <fcppt/log/object_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <filesystem>
#include <utility>
#include <fcppt/config/external_end.hpp>


sanguis::client::load::model::part_result
sanguis::client::load::model::make_parts(
	fcppt::log::object &_log,
	std::filesystem::path const &_path,
	sanguis::client::load::resource::context const &_context
)
{
	sanguis::model::object const loaded_object(
		sanguis::model::deserialize(
			sanguis::load::model::path_to_json_file(
				_path
			)
		)
	);

	sanguis::client::load::model::global_parameters const parameters(
		_path,
		_context.textures(),
		_context.sounds(),
		loaded_object.cell_size(),
		loaded_object.animation_delay(),
		loaded_object.image_name()
	);

	return
		sanguis::client::load::model::part_result(
			loaded_object.cell_size(),
			fcppt::algorithm::map<
				sanguis::client::load::model::part_map
			>(
				loaded_object.parts(),
				[
					&_log,
					&parameters
				](
					sanguis::model::part_map::value_type const &_part_pair
				)
				{
					return
						std::make_pair(
							_part_pair.first.get(),
							fcppt::make_unique_ptr<
								sanguis::client::load::model::part
							>(
								_log,
								_part_pair.second,
								parameters.new_image(
									_part_pair.second.image_name()
								)
							)
						);
				}
			)
		);
}
