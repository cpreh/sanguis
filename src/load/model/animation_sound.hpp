#ifndef SANGUIS_LOAD_MODEL_ANIMATION_SOUND_HPP_INCLUDED
#define SANGUIS_LOAD_MODEL_ANIMATION_SOUND_HPP_INCLUDED

#include "animation_sound_fwd.hpp"
#include "conditional_sound_fwd.hpp"
#include "../resource/sounds_fwd.hpp"
#include "../../animation_sound_type.hpp"
#include <sge/audio/sound/positional_ptr.hpp>
#include <sge/parse/json/member_vector.hpp>
#include <fcppt/noncopyable.hpp>
#include <boost/ptr_container/ptr_map.hpp>

namespace sanguis
{
namespace load
{
namespace model
{

class animation_sound
{
	FCPPT_NONCOPYABLE(
		animation_sound
	);
public:
	sge::audio::sound::positional_ptr const
	operator[](
		animation_sound_type::type
	) const;
	
	animation_sound();

	animation_sound(
		sge::parse::json::member_vector const &,
		resource::sounds const &
	);

	~animation_sound();
private:
	typedef boost::ptr_map<
		animation_sound_type::type,
		model::conditional_sound
	> animation_sound_map;

	animation_sound_map sounds_;
};

}
}
}

#endif
