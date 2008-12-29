#ifndef SANGUIS_DRAW_FACTORY_ENTITY_HPP_INCLUDED
#define SANGUIS_DRAW_FACTORY_ENTITY_HPP_INCLUDED

#include "../entity_auto_ptr.hpp"
#include "../system_fwd.hpp"
#include "../../entity_id.hpp"
#include "../../entity_type.hpp"

namespace sanguis
{
namespace draw
{
class environment;
namespace factory
{

entity_auto_ptr
entity(
	environment const &,
	entity_id,
	system &,
	entity_type::type);

}
}
}

#endif
