#ifndef SANGUIS_DRAW_FACTORY_TYPES_HPP_INCLUDED
#define SANGUIS_DRAW_FACTORY_TYPES_HPP_INCLUDED

#include <sge/auto_ptr.hpp>

namespace sanguis
{
namespace draw
{

class entity;

namespace factory
{

typedef sge::auto_ptr<
	draw::entity
> entity_ptr;

}
}
}

#endif
