#ifndef SANGUIS_CLIENT_DRAW2D_PARTICLE_GENERATOR_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_PARTICLE_GENERATOR_HPP_INCLUDED

#include "align_type.hpp"
#include "container.hpp"
#include "depth.hpp"
#include "dispersion_range.hpp"
#include "generation_callback.hpp"
#include "gen_frequency.hpp"
#include "gen_life_time.hpp"
#include "movement_type.hpp"
#include "uniform_rotation.hpp"
#include "uniform_velocity_range.hpp"
#include "rotation.hpp"
#include "rotation_speed.hpp"
#include "rot_speed_range.hpp"
#include "spawn_initial.hpp"
#include "speed_range.hpp"
#include "../../../diff_clock.hpp"
#include "../../../time_delta_fwd.hpp"
#include <fcppt/random/uniform.hpp>
#include <fcppt/minmax_pair_decl.hpp>
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
	public particle::container
{
	FCPPT_NONCOPYABLE(
		generator
	);
public:
	generator(
		particle::generation_callback,
		draw2d::center const &,
		particle::gen_life_time const &,
		particle::gen_frequency const &,
		particle::spawn_initial,
		particle::align_type::type,
		particle::depth,
		particle::dispersion_range const &,
		particle::speed_range const &,
		particle::rot_speed_range const &,
		particle::movement_type::type
	);

	~generator();

	bool
	update(
		sanguis::time_delta const &,
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
		particle::dispersion_range::value_type::value_type
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
