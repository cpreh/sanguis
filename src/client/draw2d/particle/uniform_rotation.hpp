#ifndef SANGUIS_CLIENT_DRAW2D_PARTICLE_UNIFORM_ROTATION_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_PARTICLE_UNIFORM_ROTATION_HPP_INCLUDED

#include "rotation.hpp"
#include <fcppt/random/uniform_fwd.hpp>

namespace sanguis
{
namespace client
{
namespace draw2d
{
namespace particle
{

typedef	fcppt::random::uniform<
	rotation
> uniform_rotation;

}
}
}
}

#endif
