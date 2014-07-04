#ifndef SANGUIS_CLIENT_DRAW2D_FACTORY_WEAPON_PICKUP_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_FACTORY_WEAPON_PICKUP_HPP_INCLUDED

#include <sanguis/weapon_description_fwd.hpp>
#include <sanguis/client/draw2d/entities/unique_ptr.hpp>
#include <sanguis/client/draw2d/entities/model/load_parameters_fwd.hpp>


namespace sanguis
{
namespace client
{
namespace draw2d
{
namespace factory
{

sanguis::client::draw2d::entities::unique_ptr
weapon_pickup(
	sanguis::client::draw2d::entities::model::load_parameters const &,
	sanguis::weapon_description const &
);

}
}
}
}

#endif
