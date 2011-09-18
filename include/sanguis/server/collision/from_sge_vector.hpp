#ifndef SANGUIS_SERVER_COLLISION_FROM_SGE_VECTOR_HPP_INCLUDED
#define SANGUIS_SERVER_COLLISION_FROM_SGE_VECTOR_HPP_INCLUDED

#include <sanguis/server/vector.hpp>
#include <sge/projectile/vector2.hpp>

namespace sanguis
{
namespace server
{
namespace collision
{

server::vector const
from_sge_vector(
	sge::projectile::vector2 const &
);

}
}
}

#endif
