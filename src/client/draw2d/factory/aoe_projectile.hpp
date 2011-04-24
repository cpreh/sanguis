#ifndef SANGUIS_CLIENT_DRAW2D_FACTORY_AOE_PROJECTILE_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_FACTORY_AOE_PROJECTILE_HPP_INCLUDED

#include "../entities/unique_ptr.hpp"
#include "../entities/model/parameters_fwd.hpp"
#include "../sprite/particle/system.hpp"
#include "../insert_own_callback.hpp"
#include "../aoe.hpp"
#include "../../../aoe_projectile_type.hpp"

namespace sanguis
{
namespace client
{
namespace draw2d
{
namespace factory
{

entities::unique_ptr
aoe_projectile(
	entities::model::parameters const &,
	sprite::particle::system &,
	draw2d::insert_own_callback const &,
	aoe_projectile_type::type,
	draw2d::aoe
);

}
}
}
}

#endif
