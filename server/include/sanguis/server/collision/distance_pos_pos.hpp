#ifndef SANGUIS_SERVER_COLLISION_DISTANCE_POS_POS_HPP_INCLUDED
#define SANGUIS_SERVER_COLLISION_DISTANCE_POS_POS_HPP_INCLUDED

#include <sanguis/server/space_unit.hpp>
#include <sanguis/server/vector_fwd.hpp>


namespace sanguis
{
namespace server
{
namespace collision
{

sanguis::server::space_unit
distance_pos_pos(
	sanguis::server::vector const &,
	sanguis::server::vector const &
);

}
}
}

#endif
