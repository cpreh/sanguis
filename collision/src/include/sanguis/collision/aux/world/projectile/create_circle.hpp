#ifndef SANGUIS_COLLISION_AUX_WORLD_PROJECTILE_CREATE_CIRCLE_HPP_INCLUDED
#define SANGUIS_COLLISION_AUX_WORLD_PROJECTILE_CREATE_CIRCLE_HPP_INCLUDED

#include <sanguis/collision/radius_fwd.hpp>
#include <sge/projectile/shape/shared_base_ptr.hpp>


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

sge::projectile::shape::shared_base_ptr const
create_circle(
	sanguis::collision::radius
);

}
}
}
}
}

#endif
