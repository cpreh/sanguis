#include <sanguis/config_app_name.hpp>
#include <sanguis/exception.hpp>
#include <sanguis/world_id.hpp>
#include <sanguis/creator/deserialize.hpp>
#include <sanguis/creator/generate.hpp>
#include <sanguis/creator/opening_count.hpp>
#include <sanguis/creator/serialize.hpp>
#include <sanguis/creator/top_parameters.hpp>
#include <sanguis/creator/top_result.hpp>
#include <sanguis/server/world/object.hpp>
#include <sanguis/server/world/parameters.hpp>
#include <sanguis/server/world/random.hpp>
#include <sanguis/server/world/random_generator_name.hpp>
#include <sanguis/server/world/random_seed.hpp>
#include <sge/config/cache_path.hpp>
#include <fcppt/insert_to_fcppt_string.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/filesystem/create_directories_recursive_exn.hpp>
#include <fcppt/filesystem/path_to_string.hpp>
#include <fcppt/io/ifstream.hpp>
#include <fcppt/io/ofstream.hpp>
#include <fcppt/text.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/path.hpp>
#include <fcppt/config/external_end.hpp>


sanguis::server::world::object_unique_ptr
sanguis::server::world::random(
	sanguis::server::world::parameters const &_parameters,
	sanguis::creator::opening_count const _opening_count,
	sanguis::world_id const _world_id
)
{
	boost::filesystem::path const cache_path(
		sge::config::cache_path(
			sanguis::config_app_name()
		)
	);

	if(
		!boost::filesystem::exists(
			cache_path
		)
	)
		fcppt::filesystem::create_directories_recursive_exn(
			cache_path
		);

	boost::filesystem::path const world_path(
		cache_path
		/
		fcppt::insert_to_fcppt_string(
			_world_id
		)
	);

	// overwrite the world file just for testing
#if 0
	if(
		!boost::filesystem::exists(
			world_path
		)
	)
#endif
	{
		fcppt::io::ofstream stream(
			world_path
		);

		sanguis::creator::serialize(
			stream,
			sanguis::creator::generate(
				sanguis::creator::top_parameters(
					sanguis::server::world::random_generator_name(
						_parameters.random_generator()
					),
					sanguis::server::world::random_seed(
						_parameters.random_generator()
					),
					_opening_count
				)
			)
		);
	}

	fcppt::io::ifstream stream(
		world_path
	);

	if(
		!stream.is_open()
	)
		throw sanguis::exception(
			FCPPT_TEXT("Failed to open ")
			+
			fcppt::filesystem::path_to_string(
				world_path
			)
		);

	return
		fcppt::make_unique_ptr<
			sanguis::server::world::object
		>(
			_parameters,
			_world_id,
			sanguis::creator::deserialize(
				stream
			)
		);
}
