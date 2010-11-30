#ifndef SANGUIS_LOAD_MODEL_SOUND_HPP_INCLUDED
#define SANGUIS_LOAD_MODEL_SOUND_HPP_INCLUDED

#include "sound_fwd.hpp"
#include "../probability_type.hpp"
#include "../resource/sounds_fwd.hpp"
#include <sge/parse/json/member_vector.hpp>
#include <sge/audio/sound/positional_ptr.hpp>
#include <sge/audio/file_ptr.hpp>
#include <fcppt/tr1/functional.hpp>

namespace sanguis
{
namespace load
{
namespace model
{

class sound
{
public:
	sound(
		sge::parse::json::member_vector const &,
		resource::sounds const &
	);
	
	probability_type
	probability() const;	

	sge::audio::sound::positional_ptr const
	make() const;
private:
	std::tr1::reference_wrapper<
		resource::sounds const
	> ctx_;

	probability_type probability_;

	sge::audio::file_ptr file_;
};

}
}
}

#endif
