#ifndef SANGUIS_CLIENT_DRAW2D_FACTORY_AOE_PROJECTILE_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_FACTORY_AOE_PROJECTILE_HPP_INCLUDED

#include <sanguis/aoe_projectile_type_fwd.hpp>
#include <sanguis/client/draw2d/aoe.hpp>
#include <sanguis/client/draw2d/insert_own_callback.hpp>
#include <sanguis/client/draw2d/entities/unique_ptr.hpp>
#include <sanguis/client/draw2d/entities/model/parameters_fwd.hpp>


namespace sanguis
{
namespace client
{
namespace draw2d
{
namespace factory
{

sanguis::client::draw2d::entities::unique_ptr
aoe_projectile(
	sanguis::client::draw2d::entities::model::parameters const &,
	sanguis::client::draw2d::insert_own_callback const &,
	sanguis::aoe_projectile_type,
	sanguis::client::draw2d::aoe
);

}
}
}
}

#endif
