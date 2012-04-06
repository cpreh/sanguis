#ifndef SANGUIS_LOAD_MODEL_RANDOM_SOUND_HPP_INCLUDED
#define SANGUIS_LOAD_MODEL_RANDOM_SOUND_HPP_INCLUDED

#include <sanguis/random_generator_fwd.hpp>
#include <sanguis/load/model/sound_container.hpp>
#include <sanguis/load/model/sound.hpp>
#include <sanguis/load/resource/sounds_fwd.hpp>
#include <sanguis/load/probability_type.hpp>
#include <sge/parse/json/element_vector.hpp>
#include <sge/audio/sound/positional_unique_ptr.hpp>
#include <fcppt/random/variate_decl.hpp>
#include <fcppt/random/distribution/uniform_real_decl.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <vector>
#include <fcppt/config/external_end.hpp>

namespace sanguis
{
namespace load
{
namespace model
{

class random_sound
{
	FCPPT_NONCOPYABLE(
		random_sound
	);
public:
	random_sound(
		sanguis::random_generator &,
		sge::parse::json::element_vector const &,
		resource::sounds const &
	);

	~random_sound();

	sge::audio::sound::positional_unique_ptr
	random() const;
private:
	sound_container sounds_;

	typedef std::vector<
		load::probability_type
	> range_vector;

	range_vector ranges_;

	typedef fcppt::random::distribution::uniform_real<
		load::probability_type
	> distribution;

	mutable fcppt::random::variate<
		sanguis::random_generator,
		distribution
	> rng_;
};

}
}
}

#endif
