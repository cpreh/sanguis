#ifndef SANGUIS_DRAW_PARTICLE_GENERATOR_HPP_INCLUDED
#define SANGUIS_DRAW_PARTICLE_GENERATOR_HPP_INCLUDED

#include "container.hpp"
#include "align_type.hpp"
#include "movement_type.hpp"
#include "../../diff_clock.hpp"
#include <sge/random/uniform.hpp>
#include <sge/time/timer.hpp>

namespace sanguis
{
namespace draw
{
namespace particle
{

class generator : public container
{
public:
	generator(
		generation_callback,
		point const &,
		time_type life_time,
		time_type spawn_frequency,
		unsigned spawn_initial,
		align_type::type,
		container::depth_type,
		dispersion_range const &,
		velocity_range const &,
		rotation_velocity_range const &,
		movement_type::type,
		draw::environment const &);
	bool update(
		time_type,
		point const &,
		rotation_type,
		depth_type);
private:
	diff_clock clock;
	generation_callback generate_object;
	sge::time::timer frequency_timer;
	sge::time::timer life_timer;
	align_type::type const alignment;
	
	sge::random::uniform<rotation_type> dispersion_angle;
	sge::random::uniform<dispersion_range::value_type> dispersion_value;
	sge::random::uniform<rotation_type> velocity_angle;
	sge::random::uniform<velocity_range::value_type> velocity_value;
	sge::random::uniform<rotation_type> rot_angle;
	sge::random::uniform<rotation_type> rot_direction;
	sge::random::uniform<rotation_type> rot_velocity;
	movement_type::type const movement;

	void generate();
};

}
}
}

#endif
