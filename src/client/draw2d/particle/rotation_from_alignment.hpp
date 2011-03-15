#ifndef SANGUIS_CLIENT_DRAW2D_PARTICLE_ROTATION_FROM_ALIGNMENT_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_PARTICLE_ROTATION_FROM_ALIGNMENT_HPP_INCLUDED

#include "rotation.hpp"
#include "align_type.hpp"
#include "point.hpp"
#include "uniform_rotation.hpp"

namespace sanguis
{
namespace client
{
namespace draw2d
{
namespace particle
{

particle::rotation
rotation_from_alignment(
	align_type::type,
	point const &refpoint,
	uniform_rotation &rot_angle
);

}
}
}
}

#endif
