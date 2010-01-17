#ifndef SANGUIS_SERVER_COLLISION_CREATE_CIRCLE_HPP_INCLUDED
#define SANGUIS_SERVER_COLLISION_CREATE_CIRCLE_HPP_INCLUDED

#include "base_fwd.hpp"
#include "../space_unit.hpp"
#include <sge/collision/shapes/base_ptr.hpp>
#include <sge/collision/world_ptr.hpp>

namespace sanguis
{
namespace server
{
namespace collision
{

sge::collision::shapes::base_ptr const
create_circle(
	sge::collision::world_ptr,
	base &,
	space_unit radius
);

}
}
}

#endif
