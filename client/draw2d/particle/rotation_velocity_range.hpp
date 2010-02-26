#ifndef SANGUIS_CLIENT_DRAW2D_PARTICLE_ROTATION_VELOCITY_RANGE_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_PARTICLE_ROTATION_VELOCITY_RANGE_HPP_INCLUDED

#include "rotation.hpp"
#include <fcppt/random/inclusive_range.hpp>

namespace sanguis 
{
namespace client
{
namespace draw2d
{
namespace particle
{

typedef fcppt::random::inclusive_range<
	rotation
> rotation_velocity_range;

}
}
}
}

#endif
