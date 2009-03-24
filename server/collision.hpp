#ifndef SANGUIS_SERVER_COLLISION_HPP_INCLUDED
#define SANGUIS_SERVER_COLLISION_HPP_INCLUDED

#include "entities/entity_fwd.hpp"
#include "../messages/types.hpp"

namespace sanguis
{
namespace server
{
bool collides(
	entities::entity const&,
	entities::entity const&);

bool collides(
	entities::entity const&,
	messages::circle_type const&);

}
}

#endif
