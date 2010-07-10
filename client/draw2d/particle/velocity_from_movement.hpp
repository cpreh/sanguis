#ifndef SANGUIS_CLIENT_DRAW2D_PARTICLE_VELOCITY_FROM_MOVEMENT_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_PARTICLE_VELOCITY_FROM_MOVEMENT_HPP_INCLUDED

#include "movement_type.hpp"
#include "point.hpp"
#include "uniform_rotation.hpp"
#include "uniform_velocity_range.hpp"

namespace sanguis
{
namespace client
{
namespace draw2d
{
namespace particle
{

particle::point const
velocity_from_movement(
	movement_type::type,
	point const &_refpoint,
	uniform_rotation &_velocity_angle,
	uniform_velocity_range &_velocity_value
);

}
}
}
}

#endif
