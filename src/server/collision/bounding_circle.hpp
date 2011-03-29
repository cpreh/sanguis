#ifndef SANGUIS_SERVER_COLLISION_BOUNDING_CIRCLE_HPP_INCLUDED
#define SANGUIS_SERVER_COLLISION_BOUNDING_CIRCLE_HPP_INCLUDED

#include "../circle.hpp"
#include "../entities/base_fwd.hpp"

namespace sanguis
{
namespace server
{
namespace collision
{

server::circle const
bounding_circle(
	entities::base const &
);

}
}
}

#endif
