#include "sound_collection.hpp"

sanguis::load::sound_collection::sound_collection(
	sound_container const &sounds_,
	probability_type const probability_)
:
	sounds_(sounds_),
	probability_(probability_)
{}

sanguis::load::sound_container const &
sanguis::load::sound_collection::sounds() const
{
	return sounds_;
}

sanguis::load::probability_type
sanguis::load::sound_collection::probability() const
{
	return probability_;
}
