#ifndef SANGUIS_CLIENT_DRAW2D_FACTORY_WEAPON_PICKUP_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_FACTORY_WEAPON_PICKUP_HPP_INCLUDED

#include "../environment.hpp"
#include "../entity_auto_ptr.hpp"
#include "../../entity_id.hpp"
#include "../../weapon_type.hpp"

namespace sanguis
{
namespace client
{
namespace draw2d
{
namespace factory
{

entity_auto_ptr
weapon_pickup(
	environment const &,
	entity_id,
	weapon_type::type
);

}
}
}
}

#endif
