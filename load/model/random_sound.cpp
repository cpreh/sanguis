#include "random_sound.hpp"
#include "../resource/context.hpp"
#include "../resource/sounds.hpp"
#include "../sound_collection.hpp"
#include <sge/random/last_exclusive_range.hpp>

sanguis::load::model::random_sound::random_sound(
	sound_container const &sounds,
	resource::context const &ctx)
:
	sounds(sounds),
	ctx(ctx),
	rng(
		sge::random::last_exclusive_range<
			sound_container::size_type
		>(
			0,
			sounds.size()))
{}

sge::audio::sound_ptr const
sanguis::load::model::random_sound::random() const
{
	return ctx.sounds().make(
		sounds.at(
			rng()));
}
