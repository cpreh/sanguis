#ifndef SANGUIS_SERVER_COLLISION_COLLIDES_HPP_INCLUDED
#define SANGUIS_SERVER_COLLISION_COLLIDES_HPP_INCLUDED

#include "../circle.hpp"
#include "../entities/base_fwd.hpp"

namespace sanguis
{
namespace server
{
namespace collision
{

bool
collides(
	entities::base const &,
	entities::base const &
);

bool
collides(
	entities::base const &,
	server::circle const &
);

}
}
}

#endif
