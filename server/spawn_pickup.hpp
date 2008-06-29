#ifndef SANGUIS_SERVER_SPAWN_PICKUP_HPP_INCLUDED
#define SANGUIS_SERVER_SPAWN_PICKUP_HPP_INCLUDED

#include "../messages/types.hpp"

namespace sanguis
{
namespace server
{

struct environment;

void spawn_pickup(
	messages::pos_type const &,
	environment const &);

}
}

#endif
