#ifndef SANGUIS_CLIENT_DRAW2D_PARTICLE_GENERATOR_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_PARTICLE_GENERATOR_HPP_INCLUDED

#include "container.hpp"
#include "align_type.hpp"
#include "movement_type.hpp"
#include "../../diff_clock.hpp"
#include <fcppt/random/uniform.hpp>
#include <sge/time/timer.hpp>

namespace sanguis
{
namespace client
{
namespace draw2d
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
	
	fcppt::random::uniform<rotation_type> dispersion_angle;
	fcppt::random::uniform<dispersion_range::value_type> dispersion_value;
	fcppt::random::uniform<rotation_type> velocity_angle;
	fcppt::random::uniform<velocity_range::value_type> velocity_value;
	fcppt::random::uniform<rotation_type> rot_angle;
	fcppt::random::uniform<rotation_type> rot_direction;
	fcppt::random::uniform<rotation_type> rot_velocity;
	movement_type::type const movement;

	void generate();
};

}
}
}
}

#endif
