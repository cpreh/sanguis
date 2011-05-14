#include "random.hpp"
#include "object.hpp"
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/ref.hpp>

#include "../../exception.hpp"
#include <sanguis/creator/generator/deserialize.hpp>
#include <sanguis/creator/generator/result.hpp>
#include <sge/config/find_cache_path.hpp>
#include <fcppt/filesystem/create_directories_recursive.hpp>
#include <fcppt/filesystem/exists.hpp>
#include <fcppt/filesystem/path.hpp>
#include <fcppt/filesystem/path_to_string.hpp>
#include <fcppt/io/ifstream.hpp>
#include <fcppt/text.hpp>

sanguis::server::world::object_unique_ptr
sanguis::server::world::random(
	world::context &_ctx,
	server::environment::load_context &_load_context,
	server::console &_console
)
{
	// TODO: move this out of here!
	fcppt::filesystem::path const cache_path(
		sge::config::find_cache_path(
			FCPPT_TEXT("sanguis")
		)
	);

	if(
		!fcppt::filesystem::exists(
			cache_path
		)
	)
		fcppt::filesystem::create_directories_recursive(
			cache_path
		);
	
	fcppt::filesystem::path const world_path(
		cache_path
		/ FCPPT_TEXT("world01")
	);

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

	// TODO:
	return
		fcppt::make_unique_ptr<
			object
		>(
			fcppt::ref(
				_ctx
			),
			fcppt::ref(
				_load_context
			),
			fcppt::ref(
				_console
			),
			sanguis::creator::generator::deserialize(
				stream
			)
		);
}
