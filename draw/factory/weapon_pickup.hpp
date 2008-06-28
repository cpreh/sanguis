#ifndef SANGUIS_DRAW_FACTORY_WEAPON_PICKUP_HPP_INCLUDED
#define SANGUIS_DRAW_FACTORY_WEAPON_PICKUP_HPP_INCLUDED

#include "../../entity_id.hpp"
#include "../../weapon_type.hpp"
#include "types.hpp"

namespace sanguis
{
namespace draw
{
namespace factory
{

entity_ptr weapon_pickup(
	entity_id,
	weapon_type::type);

}
}
}

#endif
