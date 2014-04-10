#include <sanguis/world_id.hpp>
#include <sanguis/world_name.hpp>
#include <sanguis/creator/opening_count.hpp>
#include <sanguis/creator/top_parameters.hpp>
#include <sanguis/server/world/difficulty.hpp>
#include <sanguis/server/world/generate.hpp>
#include <sanguis/server/world/object.hpp>
#include <sanguis/server/world/object_unique_ptr.hpp>
#include <sanguis/server/world/parameters.hpp>
#include <sanguis/server/world/random.hpp>
#include <sanguis/server/world/random_generator_name.hpp>
#include <sanguis/server/world/random_seed.hpp>
#include <fcppt/insert_to_fcppt_string.hpp>
#include <fcppt/text.hpp>


sanguis::server::world::object_unique_ptr
sanguis::server::world::random(
	sanguis::server::world::parameters const &_parameters,
	sanguis::creator::opening_count const _opening_count,
	sanguis::world_id const _world_id,
	sanguis::server::world::difficulty const _difficulty
)
{
	return
		sanguis::server::world::generate(
			_parameters,
			_world_id,
			// TODO!
			sanguis::world_name(
				FCPPT_TEXT("World ")
				+
				fcppt::insert_to_fcppt_string(
					_world_id
				)
			),
			_difficulty,
			sanguis::creator::top_parameters{
				sanguis::server::world::random_generator_name(
					_parameters.random_generator()
				),
				sanguis::server::world::random_seed(
					_parameters.random_generator()
				),
				_opening_count
			}
		);
}
