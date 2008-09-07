#ifndef SANGUIS_DRAW_FACTORY_PROJECTLE_HPP_INCLUDED
#define SANGUIS_DRAW_FACTORY_PROJECTILE_HPP_INCLUDED

#include "../../entity_id.hpp"
#include "../../projectile_type.hpp"
#include "../types.hpp"
#include "types.hpp"

namespace sanguis
{
namespace draw
{
namespace factory
{

entity_ptr projectile(
	entity_id,
	system &,
	projectile_type::type);

}
}
}

#endif
