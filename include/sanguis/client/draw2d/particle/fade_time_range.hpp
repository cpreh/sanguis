#ifndef SANGUIS_CLIENT_DRAW2D_PARTICLE_FADE_TIME_RANGE_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_PARTICLE_FADE_TIME_RANGE_HPP_INCLUDED

#include <sanguis/time_unit.hpp>
#include <fcppt/random/distribution/uniform_real_fwd.hpp>

namespace sanguis
{
namespace client
{
namespace draw2d
{
namespace particle
{

typedef fcppt::random::distribution::uniform_real<
	sanguis::time_unit
> fade_time_range;

}
}
}
}

#endif
