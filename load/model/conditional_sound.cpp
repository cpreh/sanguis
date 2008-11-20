#include "conditional_sound.hpp"
#include "../sound_collection.hpp"
#include <sge/random/inclusive_range.hpp>
#include <sge/math/compare.hpp>

sanguis::load::model::conditional_sound::conditional_sound(
	sound_collection const &col)
:
	range(
		col.probability()),
	rng(
		sge::random::inclusive_range<probability_type>(
			static_cast<probability_type>(0),
			static_cast<probability_type>(1))),
	random_sound_(
		col.sounds())
{}

sge::audio::sound_ptr const
sanguis::load::model::conditional_sound::random() const
{
	// avoid the corner case in which the probability is 1
	return sge::math::compare(range, static_cast<probability_type>(1)) || rng() < range
		? random_sound_.random()
		: sge::audio::sound_ptr();
}
