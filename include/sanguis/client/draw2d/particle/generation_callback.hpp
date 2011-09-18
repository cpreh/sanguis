#ifndef SANGUIS_CLIENT_DRAW2D_PARTICLE_GENERATION_CALLBACK_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_PARTICLE_GENERATION_CALLBACK_HPP_INCLUDED

#include <sanguis/client/draw2d/particle/base_ptr.hpp>
#include <fcppt/function/object_fwd.hpp>

namespace sanguis
{
namespace client
{
namespace draw2d
{
namespace particle
{

typedef fcppt::function::object<
	base_ptr ()
> generation_callback;

}
}
}
}

#endif
