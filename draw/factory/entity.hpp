#ifndef SANGUIS_DRAW_FACTORY_ENTITY_HPP_INCLUDED
#define SANGUIS_DRAW_FACTORY_ENTITY_HPP_INCLUDED

#include "types.hpp"
#include "../types.hpp"
#include "../../entity_id.hpp"
#include "../../entity_type.hpp"

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
entity(
	load::context const &,
	entity_id,
	system &,
	entity_type::type);

}
}
}

#endif
