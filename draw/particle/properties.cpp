#include "properties.hpp"
#include <sge/minmax_pair_impl.hpp>

sanguis::draw::particle::properties::properties(
	funit const anim_speed_,
	unsigned const spawn_initial_,
	funit const gen_life_time_,
	funit const gen_frequency_,
	align_type::type const align_,
	dispersion_range const &dispersion_,
	speed_range const &speed_,
	rot_speed_range const &rot_speed_,
	bool const do_fade_,
	fade_range const &fade_,
	movement_type::type const movement_)
:
	anim_speed_(anim_speed_),
	spawn_initial_(spawn_initial_),
	gen_life_time_(gen_life_time_),
	gen_frequency_(gen_frequency_),
	align_(align_),
	dispersion_(dispersion_),
	speed_(speed_),
	rot_speed_(rot_speed_),
	do_fade_(do_fade_),
	fade_(fade_),
	movement_(movement_)
{}

sanguis::draw::funit
sanguis::draw::particle::properties::anim_speed() const
{
	return anim_speed_;
}

unsigned
sanguis::draw::particle::properties::spawn_initial() const
{
	return spawn_initial_;
}

sanguis::draw::funit
sanguis::draw::particle::properties::gen_life_time() const
{
	return gen_life_time_;
}

sanguis::draw::funit
sanguis::draw::particle::properties::gen_frequency() const
{
	return gen_frequency_;
}

sanguis::draw::particle::align_type::type
sanguis::draw::particle::properties::align() const
{
	return align_;
}

sanguis::draw::particle::properties::dispersion_range const &
sanguis::draw::particle::properties::dispersion() const
{
	return dispersion_;
}

sanguis::draw::particle::properties::speed_range const &
sanguis::draw::particle::properties::speed() const
{
	return speed_;
}

sanguis::draw::particle::properties::rot_speed_range const &
sanguis::draw::particle::properties::rot_speed() const
{
	return rot_speed_;
}

bool
sanguis::draw::particle::properties::do_fade() const
{
	return do_fade_;
}

sanguis::draw::particle::properties::fade_range const &
sanguis::draw::particle::properties::fade() const
{
	return fade_;
}

sanguis::draw::particle::movement_type::type
sanguis::draw::particle::properties::movement() const
{
	return movement_;
}
