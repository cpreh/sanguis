#ifndef SANGUIS_LOAD_MODEL_SOUND_HPP_INCLUDED
#define SANGUIS_LOAD_MODEL_SOUND_HPP_INCLUDED

#include <sanguis/load/model/sound_fwd.hpp>
#include <sanguis/load/probability_type.hpp>
#include <sanguis/load/resource/sounds_fwd.hpp>
#include <sge/parse/json/member_map.hpp>
#include <sge/audio/sound/positional_unique_ptr.hpp>
#include <sge/audio/file_shared_ptr.hpp>
#include <fcppt/reference_wrapper.hpp>

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
		sge::parse::json::member_map const &,
		resource::sounds const &
	);

	probability_type
	probability() const;

	sge::audio::sound::positional_unique_ptr
	make() const;
private:
	fcppt::reference_wrapper<
		resource::sounds const
	> ctx_;

	probability_type probability_;

	sge::audio::file_shared_ptr file_;
};

}
}
}

#endif
