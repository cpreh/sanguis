#ifndef SANGUIS_SERVER_COLLISION_BODY_COLLISION_HPP_INCLUDED
#define SANGUIS_SERVER_COLLISION_BODY_COLLISION_HPP_INCLUDED

#include <sge/projectile/body/object_fwd.hpp>


namespace sanguis
{
namespace server
{
namespace collision
{

void
body_collision(
	sge::projectile::body::object const &,
	sge::projectile::body::object const &
);

}
}
}

#endif
