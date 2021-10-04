#ifndef SANGUIS_SERVER_GLOBAL_WORLD_CONNECTION_MAP_HPP_INCLUDED
#define SANGUIS_SERVER_GLOBAL_WORLD_CONNECTION_MAP_HPP_INCLUDED

#include <sanguis/server/global/dest_world_pair.hpp>
#include <sanguis/server/global/source_world_pair.hpp>
#include <fcppt/math/vector/comparison.hpp>
#include <fcppt/config/external_begin.hpp>
#include <map>
#include <fcppt/config/external_end.hpp>


namespace sanguis::server::global
{

using
world_connection_map
=
std::map<
	sanguis::server::global::source_world_pair,
	sanguis::server::global::dest_world_pair
>;

}

#endif
