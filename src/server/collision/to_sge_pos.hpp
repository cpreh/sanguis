#ifndef SANGUIS_SERVER_COLLISION_TO_SGE_POS_HPP_INCLUDED
#define SANGUIS_SERVER_COLLISION_TO_SGE_POS_HPP_INCLUDED

#include "../pos.hpp"
#include <sge/projectile/vector2.hpp>

namespace sanguis
{
namespace server
{
namespace collision
{

sge::projectile::vector2 const
to_sge_pos(
	server::pos const &
);

}
}
}

#endif
