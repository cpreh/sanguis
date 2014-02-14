#include <sanguis/world_id.hpp>
#include <sanguis/world_name.hpp>
#include <sanguis/creator/opening_count.hpp>
#include <sanguis/creator/seed.hpp>
#include <sanguis/creator/start_name.hpp>
#include <sanguis/creator/top_parameters.hpp>
#include <sanguis/server/dest_world_id.hpp>
#include <sanguis/server/source_world_id.hpp>
#include <sanguis/server/global/dest_world_pair.hpp>
#include <sanguis/server/global/generate_worlds.hpp>
#include <sanguis/server/global/source_world_pair.hpp>
#include <sanguis/server/global/world_connection_map.hpp>
#include <sanguis/server/global/world_map.hpp>
#include <sanguis/server/world/difficulty.hpp>
#include <sanguis/server/world/generate.hpp>
#include <sanguis/server/world/map.hpp>
#include <sanguis/server/world/object.hpp>
#include <sanguis/server/world/object_unique_ptr.hpp>
#include <sanguis/server/world/parameters.hpp>
#include <sanguis/server/world/random.hpp>
#include <fcppt/text.hpp>
#include <fcppt/assert/error.hpp>
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

	sanguis::server::world::difficulty difficulty(
		1u
	);

	auto const insert_world(
		[
			&worlds
		](
			sanguis::server::world::object_unique_ptr &&_world
		)
		{
			sanguis::world_id const id(
				_world->world_id()
			);

			FCPPT_ASSERT_ERROR(
				worlds.insert(
					std::make_pair(
						id,
						std::move(
							_world
						)
					)
				).second
			);
		}
	);

	insert_world(
		sanguis::server::world::generate(
			_parameters,
			sanguis::world_id(
				0u
			),
			sanguis::world_name(
				FCPPT_TEXT("Start Area")
			),
			difficulty,
			sanguis::creator::top_parameters(
				sanguis::creator::start_name(),
				sanguis::creator::seed{
					0u
				},
				sanguis::creator::opening_count{
					2u
				}
			)
		)
	);

	for(
		sanguis::world_id::value_type current_id(
			1u
		);
		current_id
		<
		sanguis::world_id::value_type(
			10u
		);
		++current_id
	)
	{
		sanguis::world_id const world_id(
			current_id
		);

		insert_world(
			sanguis::server::world::random(
				_parameters,
				sanguis::creator::opening_count(
					2u
				),
				world_id,
				difficulty++ // TODO: How to scale this?
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
