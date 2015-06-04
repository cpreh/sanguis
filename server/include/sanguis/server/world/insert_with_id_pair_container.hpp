#ifndef SANGUIS_SERVER_WORLD_INSERT_WITH_ID_PAIR_CONTAINER_HPP_INCLUDED
#define SANGUIS_SERVER_WORLD_INSERT_WITH_ID_PAIR_CONTAINER_HPP_INCLUDED

#include <sanguis/server/entities/with_id_fwd.hpp>
#include <sanguis/server/world/insert_pair_container.hpp>


namespace sanguis
{
namespace server
{
namespace world
{

typedef
sanguis::server::world::insert_pair_container<
	sanguis::server::entities::with_id
>
insert_with_id_pair_container;

}
}
}

#endif
