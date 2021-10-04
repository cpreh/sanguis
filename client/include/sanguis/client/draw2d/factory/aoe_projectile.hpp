#ifndef SANGUIS_CLIENT_DRAW2D_FACTORY_AOE_PROJECTILE_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_FACTORY_AOE_PROJECTILE_HPP_INCLUDED

#include <sanguis/aoe_projectile_type_fwd.hpp>
#include <sanguis/client/draw2d/aoe.hpp>
#include <sanguis/client/draw2d/insert_own_callback.hpp>
#include <sanguis/client/draw2d/speed_fwd.hpp>
#include <sanguis/client/draw2d/entities/load_parameters_fwd.hpp>
#include <sanguis/client/draw2d/entities/unique_ptr.hpp>
#include <sanguis/client/draw2d/sprite/center_fwd.hpp>
#include <sanguis/client/draw2d/sprite/rotation_fwd.hpp>


namespace sanguis::client::draw2d::factory
{

sanguis::client::draw2d::entities::unique_ptr
aoe_projectile(
	sanguis::client::draw2d::entities::load_parameters const &,
	sanguis::client::draw2d::insert_own_callback &&,
	sanguis::aoe_projectile_type,
	sanguis::client::draw2d::speed const &,
	sanguis::client::draw2d::sprite::center const &,
	sanguis::client::draw2d::sprite::rotation,
	sanguis::client::draw2d::aoe
);

}

#endif
