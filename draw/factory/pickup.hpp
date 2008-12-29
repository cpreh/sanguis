#ifndef SANGUIS_DRAW_FACTORY_PICKUP_HPP_INCLUDED
#define SANGUIS_DRAW_FACTORY_PICKUP_HPP_INCLUDED

#include "../entity_auto_ptr.hpp"
#include "../system_fwd.hpp"
#include "../../entity_id.hpp"
#include "../../pickup_type.hpp"

namespace sanguis
{
namespace draw
{
class environment;
namespace factory
{

entity_auto_ptr
pickup(
	environment const &,
	entity_id,
	system &,
	pickup_type::type);

}
}
}

#endif
