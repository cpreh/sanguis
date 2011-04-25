#ifndef SANGUIS_CLIENT_DRAW2D_PARTICLE_UNIFORM_VELOCITY_RANGE_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_PARTICLE_UNIFORM_VELOCITY_RANGE_HPP_INCLUDED

#include "funit_range.hpp"
#include <fcppt/random/uniform_fwd.hpp>
#include <fcppt/minmax_pair_decl.hpp>

namespace sanguis
{
namespace client
{
namespace draw2d
{
namespace particle
{

typedef	fcppt::random::uniform<
	funit_range::value_type
> uniform_velocity_range;

}
}
}
}

#endif
