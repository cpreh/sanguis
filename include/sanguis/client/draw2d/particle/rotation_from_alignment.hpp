#ifndef SANGUIS_CLIENT_DRAW2D_PARTICLE_ROTATION_FROM_ALIGNMENT_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_PARTICLE_ROTATION_FROM_ALIGNMENT_HPP_INCLUDED

#include <sanguis/client/draw2d/particle/align_type.hpp>
#include <sanguis/client/draw2d/particle/rotation.hpp>
#include <sanguis/client/draw2d/particle/uniform_rotation.hpp>
#include <sanguis/client/draw2d/center.hpp>

namespace sanguis
{
namespace client
{
namespace draw2d
{
namespace particle
{

particle::rotation const
rotation_from_alignment(
	particle::align_type::type,
	draw2d::center const &,
	particle::uniform_rotation &
);

}
}
}
}

#endif
