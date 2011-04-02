#ifndef SANGUIS_SERVER_COLLISION_DISTANCE_HPP_INCLUDED
#define SANGUIS_SERVER_COLLISION_DISTANCE_HPP_INCLUDED

#include "../space_unit.hpp"
#include "../vector.hpp"
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
	server::vector const &
);

server::space_unit
distance(
	server::vector const &,
	server::vector const &
);

}
}
}

#endif
