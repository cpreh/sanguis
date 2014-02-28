#include <sanguis/load/model/cell_size.hpp>
#include <sanguis/load/model/convert_cell_size.hpp>
#include <sanguis/load/model/global_parameters.hpp>
#include <sanguis/load/model/make_parts.hpp>
#include <sanguis/load/model/part.hpp>
#include <sanguis/load/model/part_map.hpp>
#include <sanguis/load/model/part_result.hpp>
#include <sanguis/load/resource/context.hpp>
#include <sanguis/model/deserialize.hpp>
#include <sanguis/model/object.hpp>
#include <sanguis/model/part_map.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/algorithm/map.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/filesystem/path.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


sanguis::load::model::part_result
sanguis::load::model::make_parts(
	boost::filesystem::path const &_path,
	sanguis::load::resource::context const &_context
)
{
	sanguis::model::object const loaded_object(
		sanguis::model::deserialize(
			_path
		)
	);

	sanguis::load::model::cell_size const cell_size(
		sanguis::load::model::convert_cell_size(
			loaded_object.cell_size()
		)
	);

	sanguis::load::model::global_parameters const parameters(
		_path,
		_context.textures(),
		_context.sounds(),
		cell_size,
		loaded_object.animation_delay(),
		loaded_object.image_name()
	);

	return
		sanguis::load::model::part_result(
			cell_size,
			fcppt::algorithm::map<
				sanguis::load::model::part_map
			>(
				loaded_object.parts(),
				[
					&parameters
				](
					sanguis::model::part_map::value_type const &_part_pair
				)
				{
					return
						std::make_pair(
							_part_pair.first,
							fcppt::make_unique_ptr<
								sanguis::load::model::part
							>(
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
