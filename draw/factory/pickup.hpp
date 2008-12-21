#ifndef SANGUIS_DRAW_FACTORY_PICKUP_HPP_INCLUDED
#define SANGUIS_DRAW_FACTORY_PICKUP_HPP_INCLUDED

#include "../../entity_id.hpp"
#include "../../pickup_type.hpp"
#include "../types.hpp"
#include "types.hpp"

namespace sanguis
{
namespace load
{
class context;
}
namespace draw
{
namespace factory
{

entity_ptr
pickup(
	load::context const &,
	entity_id,
	system &,
	pickup_type::type);

}
}
}

#endif
