#ifndef SANGUIS_LOAD_MODEL_CONDITIONAL_SOUND_HPP_INCLUDED
#define SANGUIS_LOAD_MODEL_CONDITIONAL_SOUND_HPP_INCLUDED

#include "random_sound.hpp"
#include "../resource/sounds_fwd.hpp"
#include "../probability_type.hpp"
#include <sge/parse/json/member_vector.hpp>
#include <sge/audio/sound/positional_ptr.hpp>
#include <fcppt/random/uniform.hpp>

namespace sanguis
{
namespace load
{
namespace model
{

class conditional_sound {
public:
	conditional_sound(
		sge::parse::json::member_vector const &,
		resource::sounds const &);
	
	sge::audio::sound::positional_ptr const
	random() const;
private:
	probability_type range;

	mutable fcppt::random::uniform<
		probability_type
	> rng;

	random_sound random_sound_;
};

}
}
}

#endif
