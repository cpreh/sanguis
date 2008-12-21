#ifndef SANGUIS_DRAW_PARTICLE_PROPERTIES_HPP_INCLUDED
#define SANGUIS_DRAW_PARTICLE_PROPERTIES_HPP_INCLUDED

#include "movement_type.hpp"
#include "../funit.hpp"
#include "../unit.hpp"

namespace sanguis
{
namespace draw
{
namespace particle
{

struct properties {
	funit anim_speed;
	unsigned spawn_initial;
	funit gen_life_time;
	funit gen_frequency;
	particle::align_type::type align;
	unit dispersion_min,dispersion_max;
	funit speed_min,speed_max;
	funit rot_speed_min,rot_speed_max;
	bool fade;
	funit fade_min,fade_max;
	movement_type::type movement;
};

}
}
}

#endif
