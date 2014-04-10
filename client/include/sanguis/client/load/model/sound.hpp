#ifndef SANGUIS_CLIENT_LOAD_MODEL_SOUND_HPP_INCLUDED
#define SANGUIS_CLIENT_LOAD_MODEL_SOUND_HPP_INCLUDED

#include <sanguis/client/load/model/sound_fwd.hpp>
#include <sanguis/client/load/resource/sounds_fwd.hpp>
#include <sge/audio/buffer_shared_ptr.hpp>
#include <fcppt/string.hpp>


namespace sanguis
{
namespace client
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
		sanguis::client::load::resource::sounds const &
	);

	sge::audio::buffer_shared_ptr
	buffer() const;
private:
	sge::audio::buffer_shared_ptr buffer_;
};

}
}
}
}

#endif
