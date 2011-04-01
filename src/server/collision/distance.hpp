#ifndef SANGUIS_SERVER_COLLISION_DISTANCE_HPP_INCLUDED
#define SANGUIS_SERVER_COLLISION_DISTANCE_HPP_INCLUDED

#include "../center.hpp"
#include "../space_unit.hpp"
#include "../entities/base_fwd.hpp"

namespace sanguis
{
namespace server
{
namespace collision
{

server::space_unit
distance(
	entities::base const &,
	entities::base const &
);

server::space_unit
distance(
	entities::base const &,
	server::center const &
);

server::space_unit
distance(
	server::center const &,
	server::center const &
);

}
}
}

#endif
