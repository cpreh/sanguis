#ifndef SANGUIS_SERVER_COLLISION_DISTANCE_ENTITY_ENTITY_HPP_INCLUDED
#define SANGUIS_SERVER_COLLISION_DISTANCE_ENTITY_ENTITY_HPP_INCLUDED

#include <sanguis/server/space_unit.hpp>
#include <sanguis/server/entities/base_fwd.hpp>


namespace sanguis::server::collision
{

sanguis::server::space_unit
distance_entity_entity(
	sanguis::server::entities::base const &,
	sanguis::server::entities::base const &
);

}

#endif
