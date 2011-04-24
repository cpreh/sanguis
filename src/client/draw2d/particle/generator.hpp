#ifndef SANGUIS_CLIENT_DRAW2D_PARTICLE_GENERATOR_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_PARTICLE_GENERATOR_HPP_INCLUDED

#include "align_type.hpp"
#include "container.hpp"
#include "depth.hpp"
#include "dispersion_range.hpp"
#include "generation_callback.hpp"
#include "movement_type.hpp"
#include "uniform_rotation.hpp"
#include "uniform_velocity_range.hpp"
#include "rotation.hpp"
#include "rotation_speed.hpp"
#include "rotation_velocity_range.hpp"
#include "velocity_range.hpp"
#include "../../../diff_clock.hpp"
#include "../../../time_type.hpp"
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
	FCPPT_NONCOPYABLE(
		generator
	);
public:
	generator(
		particle::generation_callback,
		draw2d::center const &,
		sanguis::time_type life_time,
		sanguis::time_type spawn_frequency,
		unsigned spawn_initial,
		particle::align_type::type,
		particle::depth,
		particle::dispersion_range const &,
		particle::velocity_range const &,
		particle::rotation_velocity_range const &,
		movement_type::type
	);

	~generator();

	bool
	update(
		sanguis::time_type,
		draw2d::center const &,
		particle::rotation,
		particle::depth
	);
private:
	void
	generate();

	sanguis::diff_clock clock_;

	particle::generation_callback generate_object_;

	sge::time::timer frequency_timer_;

	sge::time::timer life_timer_;

	particle::align_type::type const alignment_;
	
	fcppt::random::uniform<
		particle::rotation::value_type
	> dispersion_angle_;

	fcppt::random::uniform<
		dispersion_range::value_type
	> dispersion_value_;

	particle::uniform_rotation velocity_angle_;

	particle::uniform_velocity_range velocity_value_;

	particle::uniform_rotation rot_angle_;

	fcppt::random::uniform<
		particle::rotation::value_type
	> rot_direction_;

	fcppt::random::uniform<
		particle::rotation_speed::value_type
	> rot_velocity_;

	particle::movement_type::type const movement_;
};

}
}
}
}

#endif
