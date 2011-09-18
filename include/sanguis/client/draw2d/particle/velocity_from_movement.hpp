#ifndef SANGUIS_CLIENT_DRAW2D_PARTICLE_VELOCITY_FROM_MOVEMENT_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_PARTICLE_VELOCITY_FROM_MOVEMENT_HPP_INCLUDED

#include <sanguis/client/draw2d/particle/movement_type.hpp>
#include <sanguis/client/draw2d/particle/uniform_rotation.hpp>
#include <sanguis/client/draw2d/particle/uniform_velocity_range.hpp>
#include <sanguis/client/draw2d/center.hpp>
#include <sanguis/client/draw2d/speed.hpp>

namespace sanguis
{
namespace client
{
namespace draw2d
{
namespace particle
{

draw2d::speed const
velocity_from_movement(
	particle::movement_type::type,
	draw2d::center const &,
	particle::uniform_rotation &,
	particle::uniform_velocity_range &
);

}
}
}
}

#endif
