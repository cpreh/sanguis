#ifndef SANGUIS_SERVER_WORLD_MAP_HPP_INCLUDED
#define SANGUIS_SERVER_WORLD_MAP_HPP_INCLUDED

#include <sanguis/world_id.hpp>
#include <sanguis/server/world/object_unique_ptr.hpp>
#include <fcppt/config/external_begin.hpp>
#include <unordered_map>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace server
{
namespace world
{

using
map
=
std::unordered_map<
	sanguis::world_id,
	sanguis::server::world::object_unique_ptr
>;

}
}
}

#endif
