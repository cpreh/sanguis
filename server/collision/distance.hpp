#ifndef SANGUIS_SERVER_COLLISION_DISTANCE_HPP_INCLUDED
#define SANGUIS_SERVER_COLLISION_DISTANCE_HPP_INCLUDED

#include "../types.hpp"
#include "../entities/entity_fwd.hpp"

namespace sanguis
{
namespace server
{
namespace collision
{

space_unit
distance(
	entities::entity const &,
	entities::entity const &);

space_unit
distance(
	entities::entity const &,
	pos_type const &);

}
}
}

#endif
