#ifndef SANGUIS_LOAD_RANDOM_SOUND_HPP_INCLUDED
#define SANGUIS_LOAD_RANDOM_SOUND_HPP_INCLUDED

#include "../resource/context_fwd.hpp"
#include "../sound_type.hpp"
#include "../sound_container.hpp"
#include <sge/random/uniform.hpp>
#include <sge/audio/sound_fwd.hpp>

namespace sanguis
{
namespace load
{
namespace model
{

class random_sound {
public:
	random_sound(
		sound_container const &,
		resource::context const &,
		sound_type::type);

	sge::audio::sound_ptr const
	random() const;
private:
	sound_container const &sounds;
	resource::context const &ctx;
	sound_type::type const type_;
	mutable sge::random::uniform<
		sound_container::size_type
	> rng; 
};

}
}
}

#endif
