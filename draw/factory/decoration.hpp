#ifndef SANGUIS_DRAW_FACTORY_DECORATION_HPP_INCLUDED
#define SANGUIS_DRAW_FACTORY_DECORATION_HPP_INCLUDED

#include "../entity_auto_ptr.hpp"
#include "../../entity_id.hpp"
#include "../../decoration_type.hpp"

namespace sanguis
{
namespace draw
{
class environment;
namespace factory
{

entity_auto_ptr
decoration(
	environment const &,
	entity_id,
	decoration_type::type);

}
}
}

#endif
