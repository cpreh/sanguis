#ifndef SANGUIS_SERVER_WORLD_INSERT_PAIR_CONTAINER_HPP_INCLUDED
#define SANGUIS_SERVER_WORLD_INSERT_PAIR_CONTAINER_HPP_INCLUDED

#include <sanguis/server/world/insert_pair_decl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <vector>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace server
{
namespace world
{

template<
	typename Type
>
using
insert_pair_container
=
std::vector<
	sanguis::server::world::insert_pair<
		Type
	>
>;

}
}
}

#endif
