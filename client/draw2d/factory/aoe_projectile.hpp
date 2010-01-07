#ifndef SANGUIS_CLIENT_DRAW2D_FACTORY_AOE_PROJECTILE_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_FACTORY_AOE_PROJECTILE_HPP_INCLUDED

#include "../entities/auto_ptr.hpp"
#include "../entities/model/parameters_fwd.hpp"
#include "../sprite/particle/system.hpp"
#include "../insert_callback.hpp"
#include "../funit.hpp"
#include "../../../aoe_projectile_type.hpp"

namespace sanguis
{
namespace client
{
namespace draw2d
{
namespace factory
{

entities::auto_ptr
aoe_projectile(
	model::parameters const &,
	sprite::particle::system &,
	insert_callback const &,
	aoe_projectile_type::type,
	funit aoe
);

}
}
}
}

#endif
