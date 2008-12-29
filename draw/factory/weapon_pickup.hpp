#ifndef SANGUIS_DRAW_FACTORY_WEAPON_PICKUP_HPP_INCLUDED
#define SANGUIS_DRAW_FACTORY_WEAPON_PICKUP_HPP_INCLUDED

#include "../entity_auto_ptr.hpp"
#include "../system.hpp"
#include "../../entity_id.hpp"
#include "../../weapon_type.hpp"

namespace sanguis
{
namespace draw
{
class environment;
namespace factory
{

entity_auto_ptr
weapon_pickup(
	environment const &,
	entity_id,
	system &,
	weapon_type::type);

}
}
}

#endif
