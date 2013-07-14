#ifndef SANGUIS_SERVER_COLLISION_DISTANCE_ENTITY_POS_HPP_INCLUDED
#define SANGUIS_SERVER_COLLISION_DISTANCE_ENTITY_POS_HPP_INCLUDED

#include <sanguis/server/space_unit.hpp>
#include <sanguis/server/vector_fwd.hpp>
#include <sanguis/server/entities/base_fwd.hpp>


namespace sanguis
{
namespace server
{
namespace collision
{

sanguis::server::space_unit
distance_entity_pos(
	sanguis::server::entities::base const &,
	sanguis::server::vector const &
);

}
}
}

#endif
