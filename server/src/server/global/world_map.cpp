#include <sanguis/server/global/world_connection_map.hpp>
#include <sanguis/server/global/world_map.hpp>
#include <sanguis/server/world/map.hpp>
#include <sanguis/server/world/object.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


sanguis::server::global::world_map::world_map(
	sanguis::server::world::map &&_worlds,
	sanguis::server::global::world_connection_map &&_connections
)
:
	worlds_(
		std::move(
			_worlds
		)
	),
	connections_(
		std::move(
			_connections
		)
	)
{
}

sanguis::server::global::world_map::world_map(
	world_map &&
)
noexcept
= default;

sanguis::server::global::world_map &
sanguis::server::global::world_map::operator=(
	world_map &&
)
noexcept
= default;

sanguis::server::global::world_map::~world_map()
= default;

sanguis::server::world::map const &
sanguis::server::global::world_map::worlds() const
{
	return
		worlds_;
}

sanguis::server::global::world_connection_map const &
sanguis::server::global::world_map::connections() const
{
	return
		connections_;
}
