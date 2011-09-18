#ifndef SANGUIS_CLIENT_DRAW2D_PARTICLE_GENERATOR_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_PARTICLE_GENERATOR_HPP_INCLUDED

#include <sanguis/client/draw2d/particle/align_type.hpp>
#include <sanguis/client/draw2d/particle/container.hpp>
#include <sanguis/client/draw2d/particle/depth.hpp>
#include <sanguis/client/draw2d/particle/dispersion_range.hpp>
#include <sanguis/client/draw2d/particle/generation_callback.hpp>
#include <sanguis/client/draw2d/particle/gen_frequency.hpp>
#include <sanguis/client/draw2d/particle/gen_life_time.hpp>
#include <sanguis/client/draw2d/particle/movement_type.hpp>
#include <sanguis/client/draw2d/particle/uniform_rotation.hpp>
#include <sanguis/client/draw2d/particle/uniform_velocity_range.hpp>
#include <sanguis/client/draw2d/particle/rotation.hpp>
#include <sanguis/client/draw2d/particle/rotation_speed.hpp>
#include <sanguis/client/draw2d/particle/rot_speed_range.hpp>
#include <sanguis/client/draw2d/particle/spawn_initial.hpp>
#include <sanguis/client/draw2d/particle/speed_range.hpp>
#include <sanguis/diff_clock_fwd.hpp>
#include <sanguis/diff_timer.hpp>
#include <fcppt/function/object.hpp>
#include <fcppt/random/uniform.hpp>
#include <fcppt/minmax_pair_decl.hpp>

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
		sanguis::diff_clock const &,
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
		draw2d::center const &,
		particle::rotation,
		particle::depth
	);
private:
	void
	generate();

	particle::generation_callback generate_object_;

	sanguis::diff_timer frequency_timer_;

	sanguis::diff_timer life_timer_;

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
