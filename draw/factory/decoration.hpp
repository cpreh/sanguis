#ifndef SANGUIS_DRAW_FACTORY_DECORATION_HPP_INCLUDED
#define SANGUIS_DRAW_FACTORY_DECORATION_HPP_INCLUDED

#include "../../entity_id.hpp"
#include "../../decoration_type.hpp"
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
decoration(
	load::context const &,
	entity_id,
	system &,
	decoration_type::type);

}
}
}

#endif
