#ifndef SANGUIS_SERVER_COLLISION_BODY_COLLISION_HPP_INCLUDED
#define SANGUIS_SERVER_COLLISION_BODY_COLLISION_HPP_INCLUDED

#include <sanguis/collision/world/body_base_fwd.hpp>


namespace sanguis
{
namespace server
{
namespace collision
{

void
body_collision(
	sanguis::collision::world::body_base &,
	sanguis::collision::world::body_base &
);

}
}
}

#endif
