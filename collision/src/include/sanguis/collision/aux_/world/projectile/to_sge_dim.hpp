#ifndef SANGUIS_COLLISION_AUX__WORLD_PROJECTILE_TO_SGE_DIM_HPP_INCLUDED
#define SANGUIS_COLLISION_AUX__WORLD_PROJECTILE_TO_SGE_DIM_HPP_INCLUDED

#include <sanguis/collision/dim2_fwd.hpp>
#include <sge/projectile/dim2_fwd.hpp>


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

sge::projectile::dim2 const
to_sge_dim(
	sanguis::collision::dim2 const &
);

}
}
}
}
}

#endif
