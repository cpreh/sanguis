#ifndef SANGUIS_LOAD_MODEL_ANIMATION_SOUND_HPP_INCLUDED
#define SANGUIS_LOAD_MODEL_ANIMATION_SOUND_HPP_INCLUDED

#include <sanguis/animation_sound_type.hpp>
#include <sanguis/random_generator_fwd.hpp>
#include <sanguis/load/model/animation/sound_fwd.hpp>
#include <sanguis/load/model/conditional_sound_fwd.hpp>
#include <sanguis/load/resource/sounds_fwd.hpp>
#include <sge/audio/sound/positional_unique_ptr.hpp>
#include <sge/parse/json/member_map.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/ptr_container/ptr_map.hpp>
#include <fcppt/config/external_end.hpp>

namespace sanguis
{
namespace load
{
namespace model
{
namespace animation
{

class sound
{
	FCPPT_NONCOPYABLE(
		sound
	);
public:
	sge::audio::sound::positional_unique_ptr
	operator[](
		sanguis::animation_sound_type::type
	) const;

	sound();

	sound(
		sanguis::random_generator &,
		sge::parse::json::member_map const &,
		resource::sounds const &
	);

	~sound();
private:
	typedef boost::ptr_map<
		sanguis::animation_sound_type::type,
		model::conditional_sound
	> sound_map;

	sound_map sounds_;
};

}
}
}
}

#endif
