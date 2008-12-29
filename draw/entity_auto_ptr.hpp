#ifndef SANGUIS_DRAW_ENTITY_AUTO_PTR_HPP_INCLUDED
#define SANGUIS_DRAW_ENTITY_AUTO_PTR_HPP_INCLUDED

#include <sge/auto_ptr.hpp>

namespace sanguis
{
namespace draw
{

class entity;

typedef sge::auto_ptr<
	entity
> entity_auto_ptr;

}
}

#endif
