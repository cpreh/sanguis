#ifndef SANGUIS_LOAD_MODEL_CONDITIONAL_SOUND_HPP_INCLUDED
#define SANGUIS_LOAD_MODEL_CONDITIONAL_SOUND_HPP_INCLUDED

#include <sanguis/random_generator_fwd.hpp>
#include <sanguis/load/model/conditional_sound_fwd.hpp>
#include <sanguis/load/model/random_sound.hpp>
#include <sanguis/load/resource/sounds_fwd.hpp>
#include <sanguis/load/probability_type.hpp>
#include <sge/parse/json/member_map.hpp>
#include <sge/audio/sound/positional_unique_ptr.hpp>
#include <fcppt/random/variate_decl.hpp>
#include <fcppt/random/distribution/uniform_real_decl.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/optional_decl.hpp>

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
		sanguis::random_generator &,
		sge::parse::json::member_map const &,
		resource::sounds const &
	);

	~conditional_sound();

	sge::audio::sound::positional_unique_ptr
	random() const;
private:
	typedef fcppt::optional<
		double
	> optional_probability;

	optional_probability const range_;

	typedef fcppt::random::distribution::uniform_real<
		load::probability_type
	> distribution;

	mutable fcppt::random::variate<
		sanguis::random_generator,
		distribution
	> rng_;

	random_sound random_sound_;
};

}
}
}

#endif
