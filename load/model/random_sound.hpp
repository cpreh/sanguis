#ifndef SANGUIS_LOAD_MODEL_RANDOM_SOUND_HPP_INCLUDED
#define SANGUIS_LOAD_MODEL_RANDOM_SOUND_HPP_INCLUDED

#include "sound_container.hpp"
#include "sound.hpp"
#include "../resource/sounds_fwd.hpp"
#include "../probability_type.hpp"
#include <sge/parse/json/element_vector.hpp>
#include <sge/random/uniform.hpp>
#include <sge/audio/sound_fwd.hpp>
#include <vector>

namespace sanguis
{
namespace load
{
namespace model
{

class random_sound {
public:
	random_sound(
		sge::parse::json::element_vector const &,
		resource::sounds const &);

	sge::audio::sound_ptr const
	random() const;
private:
	sound_container sounds_;

	typedef std::vector<
		probability_type
	> range_vector;

	range_vector ranges;

	mutable sge::random::uniform<
		probability_type
	> rng; 
};

}
}
}

#endif
