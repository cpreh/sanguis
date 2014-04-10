#include <sanguis/client/load/model/sound.hpp>
#include <sanguis/client/load/resource/sounds.hpp>
#include <sge/audio/buffer_shared_ptr.hpp>
#include <fcppt/string.hpp>


sanguis::client::load::model::sound::sound(
	fcppt::string const &_file,
	sanguis::client::load::resource::sounds const &_resources
)
:
	buffer_(
		_resources.load(
			_file
		)
	)
{
}

sge::audio::buffer_shared_ptr
sanguis::client::load::model::sound::buffer() const
{
	return
		buffer_;
}
