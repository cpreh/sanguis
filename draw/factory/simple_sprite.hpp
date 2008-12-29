#ifndef SANGUIS_DRAW_FACTORY_SIMPLE_SPRITE_HPP_INCLUDED
#define SANGUIS_DRAW_FACTORY_SIMPLE_SPRITE_HPP_INCLUDED

#include "../entity.hpp"
#include "../z_ordering.hpp"
#include "../entity_auto_ptr.hpp"
#include "../system_fwd.hpp"
#include <sge/string.hpp>

namespace sanguis
{
namespace draw
{
class environment;
namespace factory
{

entity_auto_ptr
simple_sprite(
	environment const &,
	entity_id,
	system &,
	z_ordering::type,
	sge::string const &texture_name);

}
}
}

#endif
