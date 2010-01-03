#ifndef SANGUIS_DRAW_ENTITY_AUTO_PTR_HPP_INCLUDED
#define SANGUIS_DRAW_ENTITY_AUTO_PTR_HPP_INCLUDED

#include "entity_fwd.hpp"
#include <fcppt/auto_ptr.hpp>

namespace sanguis
{
namespace draw
{
typedef fcppt::auto_ptr<
	entity
> entity_auto_ptr;

}
}

#endif
