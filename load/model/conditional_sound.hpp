#ifndef SANGUIS_LOAD_MODEL_CONDITIONAL_SOUND_HPP_INCLUDED
#define SANGUIS_LOAD_MODEL_CONDITIONAL_SOUND_HPP_INCLUDED

#include "random_sound.hpp"
#include <sge/audio/sound_fwd.hpp>
#include <sge/random/uniform.hpp>
#include <sge/su.hpp>

namespace sanguis
{
namespace load
{

class sound_collection;

namespace model
{

class conditional_sound {
public:
	explicit conditional_sound(
		sound_collection const &);
	
	sge::audio::sound_ptr const
	random() const;
private:
	sge::space_unit range;
	mutable sge::random::uniform<
		sge::space_unit
	> rng;

	random_sound random_sound_;
};

}
}
}

#endif
