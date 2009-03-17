#ifndef SANGUIS_DRAW_FACTORY_SIMPLE_SPRITE_HPP_INCLUDED
#define SANGUIS_DRAW_FACTORY_SIMPLE_SPRITE_HPP_INCLUDED

#include "../entity.hpp"
#include "../z_ordering.hpp"
#include "../entity_auto_ptr.hpp"
#include <sge/string.hpp>
#include <sge/sprite/repetition_type.hpp>

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
	z_ordering::type,
	sge::string const &texture_name,
	sge::sprite::repetition_type = static_cast<sge::sprite::repetition_type>(1));

}
}
}

#endif
