#ifndef SANGUIS_CLIENT_DRAW2D_FACTORY_WEAPON_PICKUP_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_FACTORY_WEAPON_PICKUP_HPP_INCLUDED

#include <sanguis/weapon_description_fwd.hpp>
#include <sanguis/client/draw2d/entities/load_parameters_fwd.hpp>
#include <sanguis/client/draw2d/entities/unique_ptr.hpp>
#include <sanguis/client/draw2d/sprite/center_fwd.hpp>
#include <sanguis/client/draw2d/sprite/rotation_fwd.hpp>


namespace sanguis::client::draw2d::factory
{

sanguis::client::draw2d::entities::unique_ptr
weapon_pickup(
	sanguis::client::draw2d::entities::load_parameters const &,
	sanguis::client::draw2d::sprite::center const &,
	sanguis::client::draw2d::sprite::rotation,
	sanguis::weapon_description const &
);

}

#endif
