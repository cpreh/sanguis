#ifndef SANGUIS_CLIENT_DRAW2D_PARTICLE_BASE_PTR_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_PARTICLE_BASE_PTR_HPP_INCLUDED

#include "base_fwd.hpp"
#include <fcppt/unique_ptr.hpp>

namespace sanguis
{
namespace client
{
namespace draw2d
{
namespace particle
{

typedef fcppt::unique_ptr<
	base
> base_ptr;

}
}
}
}

#endif
