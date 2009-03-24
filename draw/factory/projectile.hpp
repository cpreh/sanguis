#ifndef SANGUIS_DRAW_FACTORY_PROJECTILE_HPP_INCLUDED
#define SANGUIS_DRAW_FACTORY_PROJECTILE_HPP_INCLUDED

#include "../entity_auto_ptr.hpp"
#include "../environment_fwd.hpp"
#include "../../entity_id.hpp"
#include "../../projectile_type.hpp"

namespace sanguis
{
namespace draw
{
namespace factory
{

entity_auto_ptr
projectile(
	environment const &,
	entity_id,
	projectile_type::type);

}
}
}

#endif
