#ifndef SANGUIS_SERVER_SPAWN_PICKUP_HPP_INCLUDED
#define SANGUIS_SERVER_SPAWN_PICKUP_HPP_INCLUDED

#include "environment_fwd.hpp"
#include "../messages/types.hpp"

namespace sanguis
{
namespace server
{
void spawn_pickup(
	messages::pos_type const &,
	environment const &);

}
}

#endif
