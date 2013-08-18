#ifndef SANGUIS_LOAD_MODEL_SOUND_HPP_INCLUDED
#define SANGUIS_LOAD_MODEL_SOUND_HPP_INCLUDED

#include <sanguis/load/model/sound_fwd.hpp>
#include <sanguis/load/resource/sounds_fwd.hpp>
#include <sge/audio/buffer_shared_ptr.hpp>
#include <fcppt/string.hpp>


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
		fcppt::string const &name,
		sanguis::load::resource::sounds const &
	);

	sge::audio::buffer_shared_ptr
	buffer() const;
private:
	sge::audio::buffer_shared_ptr buffer_;
};

}
}
}

#endif
