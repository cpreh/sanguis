#include "properties.hpp"
#include <fcppt/minmax_pair_impl.hpp>

sanguis::client::draw2d::particle::properties::properties(
	funit const _anim_speed,
	unsigned const _spawn_initial,
	funit const _gen_life_time,
	funit const _gen_frequency,
	align_type::type const _align,
	dispersion_range const &_dispersion,
	speed_range const &_speed,
	rot_speed_range const &_rot_speed,
	bool const _do_fade,
	fade_range const &_fade,
	movement_type::type const _movement
)
:
	anim_speed_(_anim_speed),
	spawn_initial_(_spawn_initial),
	gen_life_time_(_gen_life_time),
	gen_frequency_(_gen_frequency),
	align_(_align),
	dispersion_(_dispersion),
	speed_(_speed),
	rot_speed_(_rot_speed),
	do_fade_(_do_fade),
	fade_(_fade),
	movement_(_movement)
{}

sanguis::client::draw2d::funit
sanguis::client::draw2d::particle::properties::anim_speed() const
{
	return anim_speed_;
}

unsigned
sanguis::client::draw2d::particle::properties::spawn_initial() const
{
	return spawn_initial_;
}

sanguis::client::draw2d::funit
sanguis::client::draw2d::particle::properties::gen_life_time() const
{
	return gen_life_time_;
}

sanguis::client::draw2d::funit
sanguis::client::draw2d::particle::properties::gen_frequency() const
{
	return gen_frequency_;
}

sanguis::client::draw2d::particle::align_type::type
sanguis::client::draw2d::particle::properties::align() const
{
	return align_;
}

sanguis::client::draw2d::particle::properties::dispersion_range const &
sanguis::client::draw2d::particle::properties::dispersion() const
{
	return dispersion_;
}

sanguis::client::draw2d::particle::properties::speed_range const &
sanguis::client::draw2d::particle::properties::speed() const
{
	return speed_;
}

sanguis::client::draw2d::particle::properties::rot_speed_range const &
sanguis::client::draw2d::particle::properties::rot_speed() const
{
	return rot_speed_;
}

bool
sanguis::client::draw2d::particle::properties::do_fade() const
{
	return do_fade_;
}

sanguis::client::draw2d::particle::properties::fade_range const &
sanguis::client::draw2d::particle::properties::fade() const
{
	return fade_;
}

sanguis::client::draw2d::particle::movement_type::type
sanguis::client::draw2d::particle::properties::movement() const
{
	return movement_;
}
