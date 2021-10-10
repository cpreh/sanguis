#ifndef SANGUIS_SERVER_ENTITIES_COMBINE_REMOVE_FROM_WORLD_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_COMBINE_REMOVE_FROM_WORLD_HPP_INCLUDED

#include <sanguis/server/entities/remove_from_world_result_fwd.hpp>

namespace sanguis::server::entities
{

sanguis::server::entities::remove_from_world_result combine_remove_from_world(
    sanguis::server::entities::remove_from_world_result &&,
    sanguis::server::entities::remove_from_world_result &&);

}

#endif
