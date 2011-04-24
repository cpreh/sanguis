#ifndef SANGUIS_CLIENT_DRAW2D_FACTORY_WEAPON_PICKUP_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_FACTORY_WEAPON_PICKUP_HPP_INCLUDED

#include "../entities/unique_ptr.hpp"
#include "../entities/model/parameters_fwd.hpp"
#include "../../../weapon_type.hpp"

namespace sanguis
{
namespace client
{
namespace draw2d
{
namespace factory
{

entities::unique_ptr
weapon_pickup(
	entities::model::parameters const &,
	weapon_type::type
);

}
}
}
}

#endif
