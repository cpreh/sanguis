#ifndef SANGUIS_LOAD_MODEL_ANIMATION_SOUND_HPP_INCLUDED
#define SANGUIS_LOAD_MODEL_ANIMATION_SOUND_HPP_INCLUDED

#include "conditional_sound.hpp"
#include "../../animation_sound_type.hpp"
#include <sge/audio/sound_fwd.hpp>
#include <sge/filesystem/path.hpp>
#include <map>

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

class animation_sound {
public:
	sge::audio::sound_ptr const
	operator[](
		animation_sound_type::type) const;
private:
/*	animation_sound(
		sge::filesystem::path const &,
		resource::context const &);
	
	friend class animation;

	typedef std::map<
		animation_sound_type::type,
		conditional_sound
	> animation_sound_map;

	animation_sound_map sounds;*/
};

}
}
}

#endif
