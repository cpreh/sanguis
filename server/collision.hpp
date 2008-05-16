#ifndef SANGUIS_SERVER_COLLISSION_HPP_INCLUDED
#define SANGUIS_SERVER_COLLISSION_HPP_INCLUDED

#include "../messages/types.hpp"

namespace sanguis
{
namespace server
{
namespace entities
{
class entity;
}

bool collides(
	entities::entity const&,
	entities::entity const&);

bool collides(
	entities::entity const&,
	messages::circle_type const&);

}
}

#endif
