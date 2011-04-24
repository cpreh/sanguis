#ifndef SANGUIS_CLIENT_DRAW2D_PARTICLE_VELOCITY_FROM_MOVEMENT_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_PARTICLE_VELOCITY_FROM_MOVEMENT_HPP_INCLUDED

#include "movement_type.hpp"
#include "uniform_rotation.hpp"
#include "uniform_velocity_range.hpp"
#include "../center.hpp"
#include "../speed.hpp"

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
