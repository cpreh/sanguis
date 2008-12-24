#include "random_animation.hpp"
#include "animation.hpp"
#include <sge/random/last_exclusive_range.hpp>

sanguis::load::particle::animation const &
sanguis::load::particle::random_animation::operator()() const
{
	return animations_.at(
		rng());
}

sanguis::load::particle::random_animation::random_animation(
	animation_container const &animations_)
:
	animations_(animations_),
	rng(
		sge::random::last_exclusive_range<
			animation_container::size_type
		>(
			0,
			animations_.size()))
{}
