#ifndef SANGUIS_LOAD_RANDOM_SOUND_HPP_INCLUDED
#define SANGUIS_LOAD_RANDOM_SOUND_HPP_INCLUDED

#include "../sound_container.hpp"
#include <sge/random/uniform.hpp>
#include <sge/audio/sound_fwd.hpp>

namespace sanguis
{
namespace load
{
namespace resource
{
class context;
}
namespace model
{

class random_sound {
public:
	random_sound(
		sound_container const &,
		resource::context const &);

	sge::audio::sound_ptr const
	random() const;
private:
	sound_container const &sounds;
	resource::context const &ctx;
	mutable sge::random::uniform<
		sound_container::size_type
	> rng; 
};

}
}
}

#endif
