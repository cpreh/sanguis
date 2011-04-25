#include "properties.hpp"
#include <fcppt/minmax_pair_impl.hpp>

sanguis::client::draw2d::particle::properties::properties(
	particle::anim_speed const _anim_speed,
	particle::spawn_initial const _spawn_initial,
	particle::gen_life_time const _gen_life_time,
	particle::gen_frequency const _gen_frequency,
	particle::align_type::type const _align,
	particle::dispersion_range const &_dispersion,
	particle::speed_range const &_speed,
	particle::rot_speed_range const &_rot_speed,
	particle::fade const _fade,
	particle::fade_range const &_fade_range,
	particle::movement_type::type const _movement
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
	fade_(_fade),
	fade_range_(_fade_range),
	movement_(_movement)
{
}

sanguis::client::draw2d::particle::anim_speed const
sanguis::client::draw2d::particle::properties::anim_speed() const
{
	return anim_speed_;
}

sanguis::client::draw2d::particle::spawn_initial const
sanguis::client::draw2d::particle::properties::spawn_initial() const
{
	return spawn_initial_;
}

sanguis::client::draw2d::particle::gen_life_time const
sanguis::client::draw2d::particle::properties::gen_life_time() const
{
	return gen_life_time_;
}

sanguis::client::draw2d::particle::gen_frequency const
sanguis::client::draw2d::particle::properties::gen_frequency() const
{
	return gen_frequency_;
}

sanguis::client::draw2d::particle::align_type::type
sanguis::client::draw2d::particle::properties::align() const
{
	return align_;
}

sanguis::client::draw2d::particle::dispersion_range const &
sanguis::client::draw2d::particle::properties::dispersion() const
{
	return dispersion_;
}

sanguis::client::draw2d::particle::speed_range const &
sanguis::client::draw2d::particle::properties::speed() const
{
	return speed_;
}

sanguis::client::draw2d::particle::rot_speed_range const &
sanguis::client::draw2d::particle::properties::rot_speed() const
{
	return rot_speed_;
}

sanguis::client::draw2d::particle::fade const
sanguis::client::draw2d::particle::properties::fade() const
{
	return fade_;
}

sanguis::client::draw2d::particle::fade_range const &
sanguis::client::draw2d::particle::properties::fade_range() const
{
	return fade_range_;
}

sanguis::client::draw2d::particle::movement_type::type
sanguis::client::draw2d::particle::properties::movement() const
{
	return movement_;
}
