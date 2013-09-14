#ifndef SANGUIS_COLLISION_AUX__WORLD_PROJECTILE_FROM_SGE_VECTOR_HPP_INCLUDED
#define SANGUIS_COLLISION_AUX__WORLD_PROJECTILE_FROM_SGE_VECTOR_HPP_INCLUDED

#include <sanguis/collision/vector2_fwd.hpp>
#include <sge/projectile/vector2_fwd.hpp>


namespace sanguis
{
namespace collision
{
namespace aux_
{
namespace world
{
namespace projectile
{

sanguis::collision::vector2 const
from_sge_vector(
	sge::projectile::vector2 const &
);

}
}
}
}
}

#endif
