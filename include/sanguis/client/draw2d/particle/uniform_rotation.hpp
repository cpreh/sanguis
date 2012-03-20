#ifndef SANGUIS_CLIENT_DRAW2D_PARTICLE_UNIFORM_ROTATION_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_PARTICLE_UNIFORM_ROTATION_HPP_INCLUDED

#include <sanguis/random_generator_fwd.hpp>
#include <sanguis/client/draw2d/particle/rotation.hpp>
#include <fcppt/random/variate_fwd.hpp>
#include <fcppt/random/distribution/uniform_real_fwd.hpp>


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
		particle::rotation::value_type
	>
> uniform_rotation;

}
}
}
}

#endif
