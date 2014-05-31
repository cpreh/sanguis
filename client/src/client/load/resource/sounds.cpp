#include <sanguis/media_path.hpp>
#include <sanguis/client/load/resource/map_get_or_create.hpp>
#include <sanguis/client/load/resource/sounds.hpp>
#include <sge/audio/buffer.hpp>
#include <sge/audio/buffer_shared_ptr.hpp>
#include <sge/audio/file.hpp>
#include <sge/audio/loader.hpp>
#include <sge/audio/optional_file_unique_ptr.hpp>
#include <sge/audio/player.hpp>
#include <fcppt/text.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/filesystem/path.hpp>
#include <fcppt/config/external_end.hpp>


sanguis::client::load::resource::sounds::sounds(
	sge::audio::loader &_multi_loader,
	sge::audio::player &_player
)
:
	multi_loader_(
		_multi_loader
	),
	player_(
		_player
	),
	buffers_()
{
}

sanguis::client::load::resource::sounds::~sounds()
{
}

sge::audio::buffer_shared_ptr
sanguis::client::load::resource::sounds::load(
	fcppt::string const &_name
) const
{
	return
		this->load_path(
			sanguis::media_path()
			/
			FCPPT_TEXT("sound")
			/
			_name
		);
}

sge::audio::buffer_shared_ptr
sanguis::client::load::resource::sounds::load_path(
	boost::filesystem::path const &_path
) const
{
	return
		sanguis::client::load::resource::map_get_or_create(
			buffers_,
			_path,
			[
				this
			](
				boost::filesystem::path const &path
			)
			{
				sge::audio::optional_file_unique_ptr const file(
					multi_loader_.load(
						path
					)
				);

				return
					file
					?
						sge::audio::buffer_shared_ptr(
							player_.create_buffer(
								**file
							)
						)
					:
						sge::audio::buffer_shared_ptr()
					;
			}
		);
}
