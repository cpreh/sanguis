#ifndef SANGUIS_SERVER_COLLISION_GHOST_CONTAINER_HPP_INCLUDED
#define SANGUIS_SERVER_COLLISION_GHOST_CONTAINER_HPP_INCLUDED

#include <sge/projectile/ghost/object_fwd.hpp>
#include <boost/ptr_container/ptr_vector.hpp>

namespace sanguis
{
namespace server
{
namespace collision
{

typedef boost::ptr_vector<
	sge::projectile::ghost::object
> ghost_container;

}
}
}

#endif
