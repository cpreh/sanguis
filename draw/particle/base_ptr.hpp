#ifndef SANGUIS_DRAW_PARTICLE_BASE_PTR_HPP_INCLUDED
#define  SANGUIS_DRAW_PARTICLE_BASE_PTR_HPP_INCLUDED

#include <sge/auto_ptr.hpp>

namespace sanguis
{
namespace draw
{
namespace particle
{

class base;

typedef sge::auto_ptr<
	base
> base_ptr;

}
}
}

#endif
