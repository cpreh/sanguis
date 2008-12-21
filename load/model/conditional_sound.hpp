#ifndef SANGUIS_LOAD_MODEL_CONDITIONAL_SOUND_HPP_INCLUDED
#define SANGUIS_LOAD_MODEL_CONDITIONAL_SOUND_HPP_INCLUDED

#include "random_sound.hpp"
#include "../probability_type.hpp"
#include <sge/audio/sound_fwd.hpp>
#include <sge/random/uniform.hpp>

namespace sanguis
{
namespace load
{

class sound_collection;

namespace resource
{
class context;
}
namespace model
{

class conditional_sound {
public:
	conditional_sound(
		sound_collection const &,
		resource::context const &);
	
	sge::audio::sound_ptr const
	random() const;
private:
	probability_type range;
	mutable sge::random::uniform<
		probability_type
	> rng;

	random_sound random_sound_;
};

}
}
}

#endif
