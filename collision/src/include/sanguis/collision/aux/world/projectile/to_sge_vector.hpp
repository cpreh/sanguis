#ifndef SANGUIS_COLLISION_AUX_WORLD_PROJECTILE_TO_SGE_VECTOR_HPP_INCLUDED
#define SANGUIS_COLLISION_AUX_WORLD_PROJECTILE_TO_SGE_VECTOR_HPP_INCLUDED

#include <sanguis/collision/vector2_fwd.hpp>
#include <sge/projectile/vector2_fwd.hpp>


namespace sanguis
{
namespace collision
{
namespace aux
{
namespace world
{
namespace projectile
{

sge::projectile::vector2 const
to_sge_vector(
	sanguis::collision::vector2 const &
);

}
}
}
}
}

#endif
