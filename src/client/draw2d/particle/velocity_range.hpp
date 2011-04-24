#ifndef SANGUIS_CLIENT_DRAW2D_PARTICLE_VELOCITY_RANGE_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_PARTICLE_VELOCITY_RANGE_HPP_INCLUDED

#include "../funit.hpp"
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
	draw2d::funit
> velocity_range;

}
}
}
}

#endif
