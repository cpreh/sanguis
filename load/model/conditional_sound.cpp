#include "conditional_sound.hpp"
#include "../sound_collection.hpp"
#include <sge/random/inclusive_range.hpp>

sanguis::load::model::conditional_sound::conditional_sound(
	sound_collection const &col)
:
	range(
		col.probability()),
	rng(
		sge::random::inclusive_range<sge::space_unit>(
			sge::su(0),
			col.probability())),
	random_sound_(
		col.sounds())
{}

sge::audio::sound_ptr const
sanguis::load::model::conditional_sound::random() const
{
	return rng() <= range
		? random_sound_.random()
		: sge::audio::sound_ptr();
}
