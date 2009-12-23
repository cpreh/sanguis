#ifndef SANGUIS_DRAW_PARTICLE_BASE_PTR_HPP_INCLUDED
#define SANGUIS_DRAW_PARTICLE_BASE_PTR_HPP_INCLUDED

#include "base_fwd.hpp"
#include <fcppt/auto_ptr.hpp>

namespace sanguis
{
namespace draw
{
namespace particle
{
typedef fcppt::auto_ptr<
	base
> base_ptr;

}
}
}

#endif
