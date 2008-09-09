#ifndef SANGUIS_DRAW_FACTORY_DECORATION_HPP_INCLUDED
#define SANGUIS_DRAW_FACTORY_DECORATION_HPP_INCLUDED

#include "../../entity_id.hpp"
#include "../../decoration_type.hpp"
#include "../types.hpp"
#include "types.hpp"

namespace sanguis
{
namespace draw
{
namespace factory
{

entity_ptr decoration(
	entity_id,
	system &,
	decoration_type::type);

}
}
}

#endif
