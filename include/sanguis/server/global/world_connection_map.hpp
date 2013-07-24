#ifndef SANGUIS_SERVER_GLOBAL_WORLD_CONNECTION_MAP_HPP_INCLUDED
#define SANGUIS_SERVER_GLOBAL_WORLD_CONNECTION_MAP_HPP_INCLUDED

#include <sanguis/creator/pos.hpp>
#include <sanguis/server/global/world_id_pair.hpp>
#include <fcppt/config/external_begin.hpp>
#include <map>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace server
{
namespace global
{

typedef
std::map<
	sanguis::server::global::world_id_pair,
	sanguis::creator::pos
>
world_connection_map;

}
}
}

#endif
