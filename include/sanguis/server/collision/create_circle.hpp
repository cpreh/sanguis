#ifndef SANGUIS_SERVER_COLLISION_CREATE_CIRCLE_HPP_INCLUDED
#define SANGUIS_SERVER_COLLISION_CREATE_CIRCLE_HPP_INCLUDED

#include <sanguis/server/radius.hpp>
#include <sge/projectile/shape/shared_base_ptr.hpp>


namespace sanguis
{
namespace server
{
namespace collision
{

sge::projectile::shape::shared_base_ptr const
create_circle(
	sanguis::server::radius
);

}
}
}

#endif
