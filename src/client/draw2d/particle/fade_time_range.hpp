#ifndef SANGUIS_CLIENT_DRAW2D_PARTICLE_FADE_TIME_RANGE_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_PARTICLE_FADE_TIME_RANGE_HPP_INCLUDED

#include "../../../time_unit.hpp"
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
	sanguis::time_unit
> fade_time_range;

}
}
}
}

#endif
