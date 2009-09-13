#ifndef SANGUIS_SERVER_COLLISION_CREATE_CIRCLE_HPP_INCLUDED
#define SANGUIS_SERVER_COLLISION_CREATE_CIRCLE_HPP_INCLUDED

#include "base_fwd.hpp"
#include "../space_unit.hpp"
#include "../pos_type.hpp"
#include <sge/collision/objects/base_fwd.hpp>
#include <sge/collision/world_fwd.hpp>

namespace sanguis
{
namespace server
{
namespace collision
{

sge::collision::objects::base_ptr const
create_circle(
	sge::collision::world_ptr const collision_world,
	pos_type const &center,
	space_unit direction,
	space_unit radius,
	space_unit movement_speed,
	collision::base &obj
);

}
}
}

#endif
