#ifndef SANGUIS_CLIENT_DRAW2D_PARTICLE_PROPERTIES_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_PARTICLE_PROPERTIES_HPP_INCLUDED

#include "properties_fwd.hpp"
#include "align_type.hpp"
#include "anim_speed.hpp"
#include "dispersion_range.hpp"
#include "fade.hpp"
#include "fade_range.hpp"
#include "gen_frequency.hpp"
#include "gen_life_time.hpp"
#include "movement_type.hpp"
#include "rot_speed_range.hpp"
#include "spawn_initial.hpp"
#include "speed_range.hpp"
#include <fcppt/chrono/duration_impl.hpp>
#include <fcppt/nonassignable.hpp>
#include <fcppt/minmax_pair_impl.hpp>

namespace sanguis
{
namespace client
{
namespace draw2d
{
namespace particle
{

class properties
{
	FCPPT_NONASSIGNABLE(
		properties
	);
public:
	properties(
		particle::anim_speed,
		particle::spawn_initial,
		particle::gen_life_time,
		particle::gen_frequency,
		particle::align_type::type,
		particle::dispersion_range const &,
		particle::speed_range const &,
		particle::rot_speed_range const &,
		particle::fade,
		particle::fade_range const &,
		particle::movement_type::type
	);

	particle::anim_speed const
	anim_speed() const;

	particle::spawn_initial const
	spawn_initial() const;

	particle::gen_life_time const
	gen_life_time() const;

	particle::gen_frequency const
	gen_frequency() const;

	particle::align_type::type
	align() const;

	particle::dispersion_range const &
	dispersion() const;

	particle::speed_range const &
	speed() const;

	particle::rot_speed_range const &
	rot_speed() const;

	particle::fade const
	fade() const;

	particle::fade_range const &
	fade_range() const;

	particle::movement_type::type
	movement() const;
private:
	particle::anim_speed const anim_speed_;

	particle::spawn_initial const spawn_initial_;

	particle::gen_life_time const gen_life_time_;

	particle::gen_frequency const gen_frequency_;

	particle::align_type::type const align_;

	particle::dispersion_range const dispersion_;

	particle::speed_range const speed_;

	particle::rot_speed_range const rot_speed_;

	particle::fade const fade_;

	particle::fade_range const fade_range_;

	particle::movement_type::type const movement_;
};

}
}
}
}

#endif
