#include <sanguis/server/world/random.hpp>
#include <sanguis/server/world/object.hpp>
#include <sge/charconv/system_fwd.hpp>
#include <fcppt/cref.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/ref.hpp>

#include <sanguis/exception.hpp>
#include <sanguis/creator/generator/deserialize.hpp>
#include <sanguis/creator/generator/generate.hpp>
#include <sanguis/creator/generator/name.hpp>
#include <sanguis/creator/generator/result.hpp>
#include <sanguis/creator/generator/seed.hpp>
#include <sanguis/creator/generator/serialize.hpp>
#include <sanguis/creator/generator/top_parameters.hpp>
#include <sanguis/creator/generator/size.hpp>
#include <sge/config/cache_path.hpp>
#include <fcppt/filesystem/create_directories_recursive_exn.hpp>
#include <fcppt/filesystem/path_to_string.hpp>
#include <fcppt/math/dim/object_impl.hpp>
#include <fcppt/io/ifstream.hpp>
#include <fcppt/io/ofstream.hpp>
#include <fcppt/text.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/path.hpp>
#include <fcppt/config/external_end.hpp>

sanguis::server::world::object_unique_ptr
sanguis::server::world::random(
	sanguis::diff_clock const &_diff_clock,
	sanguis::random_generator &_random_generator,
	world::context &_ctx,
	server::environment::load_context &_load_context,
	sge::charconv::system &_charconv_system,
	server::console &_console
)
{
	// TODO: move this out of here!
	boost::filesystem::path const cache_path(
		sge::config::cache_path(
			FCPPT_TEXT("sanguis")
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
		/ FCPPT_TEXT("world01")
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

		sanguis::creator::generator::serialize(
			stream,
			sanguis::creator::generator::generate(
				sanguis::creator::generator::top_parameters(
					sanguis::creator::generator::name(
						FCPPT_TEXT("car_park")
					),
					sanguis::creator::generator::seed(
						0u
					),
					sanguis::creator::generator::size(
						4000u,
						4000u
					)
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

	// TODO:
	return
		fcppt::make_unique_ptr<
			sanguis::server::world::object
		>(
			fcppt::cref(
				_diff_clock
			),
			fcppt::ref(
				_random_generator
			),
			sanguis::world_id(
				0u
			), // FIXME!
			fcppt::ref(
				_ctx
			),
			fcppt::ref(
				_load_context
			),
			fcppt::ref(
				_charconv_system
			),
			fcppt::ref(
				_console
			),
			sanguis::creator::generator::deserialize(
				stream
			)
		);
}
