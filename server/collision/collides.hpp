#ifndef SANGUIS_SERVER_COLLISION_COLLIDES_HPP_INCLUDED
#define SANGUIS_SERVER_COLLISION_COLLIDES_HPP_INCLUDED

#include "../types.hpp"
#include "../entities/entity_fwd.hpp"

namespace sanguis
{
namespace server
{
namespace collision
{

bool collides(
	entities::entity const &,
	entities::entity const &);

bool collides(
	entities::entity const &,
	circle_type const &);

}
}
}

#endif
