#ifndef SANGUIS_DRAW_FACTORY_AOE_PROJECTILE_HPP_INCLUDED
#define SANGUIS_DRAW_FACTORY_AOE_PROJECTILE_HPP_INCLUDED

#include "../entity_auto_ptr.hpp"
#include "../environment_fwd.hpp"
#include "../funit.hpp"
#include "../../entity_id.hpp"
#include "../../aoe_projectile_type.hpp"

namespace sanguis
{
namespace draw
{
namespace factory
{

entity_auto_ptr
aoe_projectile(
	environment const &,
	entity_id,
	aoe_projectile_type::type,
	funit aoe);

}
}
}

#endif
