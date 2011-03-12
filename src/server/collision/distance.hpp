#ifndef SANGUIS_SERVER_COLLISION_DISTANCE_HPP_INCLUDED
#define SANGUIS_SERVER_COLLISION_DISTANCE_HPP_INCLUDED

#include "../pos_type.hpp"
#include "../space_unit.hpp"
#include "../entities/base_fwd.hpp"

namespace sanguis
{
namespace server
{
namespace collision
{

space_unit
distance(
	entities::base const &,
	entities::base const &
);

space_unit
distance(
	entities::base const &,
	pos_type const &
);

space_unit
distance(
	pos_type const &,
	pos_type const &
);

}
}
}

#endif
