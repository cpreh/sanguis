#include <sanguis/world_id.hpp>
#include <sanguis/creator/opening_count.hpp>
#include <sanguis/server/dest_world_id.hpp>
#include <sanguis/server/source_world_id.hpp>
#include <sanguis/server/global/dest_world_pair.hpp>
#include <sanguis/server/global/generate_worlds.hpp>
#include <sanguis/server/global/source_world_pair.hpp>
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

	sanguis::server::global::world_connection_map connections;

	for(
		sanguis::world_id::value_type current_id(
			0u
		);
		current_id
		<
		sanguis::world_id::value_type(
			5u
		);
		++current_id
	)
	{
		sanguis::world_id const world_id(
			current_id
		);

		worlds.insert(
			std::make_pair(
				world_id,
				sanguis::server::world::random(
					_parameters,
					sanguis::creator::opening_count(
						2u
					),
					world_id
				)
			)
		);

		if(
			current_id == 0u
		)
			continue;

		sanguis::world_id const previous_id(
			current_id - 1u
		);

		sanguis::creator::opening const current_opening(
			worlds[
				world_id
			]->openings().at(
				0u
			)
		);

		sanguis::creator::opening const previous_opening(
			worlds[
				previous_id
			]->openings().at(
				1u
			)
		);

		connections.insert(
			std::make_pair(
				sanguis::server::global::source_world_pair(
					sanguis::server::source_world_id(
						previous_id
					),
					previous_opening
				),
				sanguis::server::global::dest_world_pair(
					sanguis::server::dest_world_id(
						world_id
					),
					current_opening
				)
			)
		);

		connections.insert(
			std::make_pair(
				sanguis::server::global::source_world_pair(
					sanguis::server::source_world_id(
						world_id
					),
					current_opening
				),
				sanguis::server::global::dest_world_pair(
					sanguis::server::dest_world_id(
						previous_id
					),
					previous_opening
				)
			)
		);
	}

	return
		sanguis::server::global::world_map(
			std::move(
				worlds
			),
			connections
		);
}
