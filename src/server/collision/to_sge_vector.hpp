#ifndef SANGUIS_SERVER_COLLISION_TO_SGE_VECTOR_HPP_INCLUDED
#define SANGUIS_SERVER_COLLISION_TO_SGE_VECTOR_HPP_INCLUDED

#include "../vector.hpp"
#include <sge/projectile/vector2.hpp>

namespace sanguis
{
namespace server
{
namespace collision
{

sge::projectile::vector2 const
to_sge_vector(
	server::vector const &
);

}
}
}

#endif
