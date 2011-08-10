#ifndef SANGUIS_LOAD_MODEL_CONDITIONAL_SOUND_HPP_INCLUDED
#define SANGUIS_LOAD_MODEL_CONDITIONAL_SOUND_HPP_INCLUDED

#include "conditional_sound_fwd.hpp"
#include "random_sound.hpp"
#include "../resource/sounds_fwd.hpp"
#include "../probability_type.hpp"
#include <sge/parse/json/member_vector.hpp>
#include <sge/audio/sound/positional_ptr.hpp>
#include <fcppt/random/uniform.hpp>
#include <fcppt/noncopyable.hpp>

namespace sanguis
{
namespace load
{
namespace model
{

class conditional_sound
{
	FCPPT_NONCOPYABLE(
		conditional_sound
	);
public:
	conditional_sound(
		sge::parse::json::member_vector const &,
		resource::sounds const &
	);

	~conditional_sound();

	sge::audio::sound::positional_ptr const
	random() const;
private:
	load::probability_type range_;

	mutable fcppt::random::uniform<
		load::probability_type
	> rng_;

	random_sound random_sound_;
};

}
}
}

#endif
