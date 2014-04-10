#ifndef SANGUIS_SERVER_GLOBAL_WORLD_MAP_HPP_INCLUDED
#define SANGUIS_SERVER_GLOBAL_WORLD_MAP_HPP_INCLUDED

#include <sanguis/server/global/world_connection_map.hpp>
#include <sanguis/server/global/world_map_fwd.hpp>
#include <sanguis/server/world/map.hpp>
#include <fcppt/noncopyable.hpp>


namespace sanguis
{
namespace server
{
namespace global
{

class world_map
{
	FCPPT_NONCOPYABLE(
		world_map
	);
public:
	world_map(
		sanguis::server::world::map &&,
		sanguis::server::global::world_connection_map const &
	);

	~world_map();

	world_map(
		world_map &&
	);

	sanguis::server::world::map const &
	worlds() const;

	sanguis::server::global::world_connection_map const &
	connections() const;
private:
	sanguis::server::world::map worlds_;

	sanguis::server::global::world_connection_map connections_;
};

}
}
}

#endif
