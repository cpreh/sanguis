#ifndef SANGUIS_CLIENT_DRAW2D_PARTICLE_UNIFORM_VELOCITY_RANGE_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_PARTICLE_UNIFORM_VELOCITY_RANGE_HPP_INCLUDED

#include <sanguis/random_generator_fwd.hpp>
#include <sanguis/client/draw2d/particle/funit_range.hpp>
#include <fcppt/random/variate_fwd.hpp>
#include <fcppt/random/distribution/uniform_real_fwd.hpp>
#include <fcppt/homogenous_pair_decl.hpp>

namespace sanguis
{
namespace client
{
namespace draw2d
{
namespace particle
{

typedef	fcppt::random::variate<
	sanguis::random_generator,
	fcppt::random::distribution::uniform_real<
		funit_range::value_type
	>
> uniform_velocity_range;

}
}
}
}

#endif
