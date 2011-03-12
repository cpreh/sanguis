#ifndef SANGUIS_CLIENT_DRAW2D_PARTICLE_GENERATOR_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_PARTICLE_GENERATOR_HPP_INCLUDED

#include "container.hpp"
#include "generation_callback.hpp"
#include "align_type.hpp"
#include "time_type.hpp"
#include "dispersion_range.hpp"
#include "velocity_range.hpp"
#include "rotation_velocity_range.hpp"
#include "movement_type.hpp"
#include "point.hpp"
#include "uniform_rotation.hpp"
#include "uniform_velocity_range.hpp"
#include "../../../diff_clock.hpp"
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

class generator
:
	public container
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
		movement_type::type
	);

	bool
	update(
		time_type,
		point const &,
		rotation_type,
		depth_type
	);
private:
	diff_clock clock_;
	generation_callback generate_object_;
	sge::time::timer frequency_timer_;
	sge::time::timer life_timer_;
	align_type::type const alignment_;
	
	fcppt::random::uniform<rotation_type> dispersion_angle_;
	fcppt::random::uniform<dispersion_range::value_type> dispersion_value_;
	uniform_rotation velocity_angle_;
	uniform_velocity_range velocity_value_;
	uniform_rotation rot_angle_;
	fcppt::random::uniform<rotation_type> rot_direction_;
	fcppt::random::uniform<rotation_type> rot_velocity_;
	movement_type::type const movement_;

	void generate();
};

}
}
}
}

#endif
