#ifndef SANGUIS_DRAW_FACTORY_SIMPLE_SPRITE_HPP_INCLUDED
#define SANGUIS_DRAW_FACTORY_SIMPLE_SPRITE_HPP_INCLUDED

#include "types.hpp"
#include "../entity.hpp"
#include "../z_ordering.hpp"
#include "../types.hpp"
#include <sge/string.hpp>

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
simple_sprite(
	load::context const &,
	entity_id,
	system &,
	z_ordering::type,
	sge::string const &texture_name);

}
}
}

#endif
