#ifndef SANGUIS_LOAD_MODEL_CONDITIONAL_SOUND_HPP_INCLUDED
#define SANGUIS_LOAD_MODEL_CONDITIONAL_SOUND_HPP_INCLUDED

#include <sanguis/load/model/conditional_sound_fwd.hpp>
#include <sanguis/load/model/random_sound.hpp>
#include <sanguis/load/resource/sounds_fwd.hpp>
#include <sanguis/load/probability_type.hpp>
#include <sge/parse/json/member_map.hpp>
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
		sge::parse::json::member_map const &,
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
