#include <sanguis/world_id.hpp>
#include <sanguis/creator/opening_count.hpp>
#include <sanguis/server/global/generate_worlds.hpp>
#include <sanguis/server/global/world_connection_map.hpp>
#include <sanguis/server/global/world_map.hpp>
#include <sanguis/server/world/map.hpp>
#include <sanguis/server/world/object.hpp>
#include <sanguis/server/world/parameters.hpp>
#include <sanguis/server/world/random.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


sanguis::server::global::world_map
sanguis::server::global::generate_worlds(
	sanguis::server::world::parameters const &_parameters
)
{
	sanguis::server::world::map worlds;

	worlds.insert(
		std::make_pair(
			// TODO!
			sanguis::world_id(
				0u
			),
			sanguis::server::world::random(
				_parameters,
				sanguis::creator::opening_count(
					2u
				),
				sanguis::world_id(
					0u
				)
			)
		)
	);

	return
		sanguis::server::global::world_map(
			std::move(
				worlds
			),
			sanguis::server::global::world_connection_map()
		);
/*
	for(
		sanguis::world_id id(
			1u
		);
		id < sanguis::world_id(10u);
		++id
	)*/

}
