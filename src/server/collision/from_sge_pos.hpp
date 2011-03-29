#ifndef SANGUIS_SERVER_COLLISION_FROM_SGE_POS_HPP_INCLUDED
#define SANGUIS_SERVER_COLLISION_FROM_SGE_POS_HPP_INCLUDED

#include "../pos.hpp"
#include <sge/projectile/vector2.hpp>

namespace sanguis
{
namespace server
{
namespace collision
{

server::pos const
from_sge_pos(
	sge::projectile::vector2 const &
);

}
}
}

#endif
