#ifndef SANGUIS_SERVER_COLLISION_BOUNDING_CIRCLE_HPP_INCLUDED
#define SANGUIS_SERVER_COLLISION_BOUNDING_CIRCLE_HPP_INCLUDED

#include "../types.hpp"
#include "../entities/entity_fwd.hpp"

namespace sanguis
{
namespace server
{
namespace collision
{

circle_type const
bounding_circle(
	entities::entity const &);

}
}
}

#endif
