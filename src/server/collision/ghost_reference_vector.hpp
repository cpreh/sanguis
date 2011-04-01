#ifndef SANGUIS_SERVER_COLLISION_GHOST_REFERENCE_VECTOR_HPP_INCLUDED
#define SANGUIS_SERVER_COLLISION_GHOST_REFERENCE_VECTOR_HPP_INCLUDED

#include <sge/projectile/ghost/object_fwd.hpp>
#include <fcppt/reference_wrapper.hpp>
#include <vector>

namespace sanguis
{
namespace server
{
namespace collision
{

typedef std::vector<
	fcppt::reference_wrapper<
		sge::projectile::ghost::object
	>
> ghost_reference_vector;

}
}
}

#endif
