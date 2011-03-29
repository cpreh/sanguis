#ifndef SANGUIS_SERVER_COLLISION_CREATE_CIRCLE_HPP_INCLUDED
#define SANGUIS_SERVER_COLLISION_CREATE_CIRCLE_HPP_INCLUDED

#include "../space_unit.hpp"
#include <sge/projectile/shapes/base_ptr.hpp>

namespace sanguis
{
namespace server
{
namespace collision
{

sge::collision::shapes::base_ptr const
create_circle(
	server::space_unit radius
);

}
}
}

#endif
