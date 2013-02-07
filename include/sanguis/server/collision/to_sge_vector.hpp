#ifndef SANGUIS_SERVER_COLLISION_TO_SGE_VECTOR_HPP_INCLUDED
#define SANGUIS_SERVER_COLLISION_TO_SGE_VECTOR_HPP_INCLUDED

#include <sanguis/server/vector_fwd.hpp>
#include <sge/projectile/vector2_fwd.hpp>


namespace sanguis
{
namespace server
{
namespace collision
{

sge::projectile::vector2 const
to_sge_vector(
	sanguis::server::vector const &
);

}
}
}

#endif
