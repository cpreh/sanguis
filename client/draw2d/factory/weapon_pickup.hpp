#ifndef SANGUIS_CLIENT_DRAW2D_FACTORY_WEAPON_PICKUP_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_FACTORY_WEAPON_PICKUP_HPP_INCLUDED

#include "../entities/auto_ptr.hpp"
#include "../../weapon_type.hpp"

namespace sanguis
{
namespace client
{
namespace draw2d
{
namespace factory
{

entities::auto_ptr
weapon_pickup(
	entities::model::parameters const &,
	weapon_type::type
);

}
}
}
}

#endif
