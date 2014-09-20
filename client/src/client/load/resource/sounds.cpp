#include <sanguis/media_path.hpp>
#include <sanguis/client/load/resource/optional_sound.hpp>
#include <sanguis/client/load/resource/sounds.hpp>
#include <sge/audio/buffer.hpp>
#include <sge/audio/buffer_unique_ptr.hpp>
#include <sge/audio/file.hpp>
#include <sge/audio/file_unique_ptr.hpp>
#include <sge/audio/loader.hpp>
#include <sge/audio/player.hpp>
#include <fcppt/optional_bind_construct.hpp>
#include <fcppt/optional_impl.hpp>
#include <fcppt/text.hpp>
#include <fcppt/container/get_or_insert.hpp>
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

sanguis::client::load::resource::optional_sound const
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

sanguis::client::load::resource::optional_sound const
sanguis::client::load::resource::sounds::load_path(
	boost::filesystem::path const &_path
) const
{
	return
		fcppt::optional_bind_construct(
			fcppt::container::get_or_insert(
				buffers_,
				_path,
				[
					this
				](
					boost::filesystem::path const &_npath
				)
				-> optional_buffer
				{
					sge::audio::optional_file_unique_ptr const opt_file{
						multi_loader_.load(
							_npath
						)
					};

					return
						fcppt::optional_bind_construct(
							opt_file,
							[
								this
							](
								sge::audio::file_unique_ptr const &_file
							)
							-> sge::audio::buffer_unique_ptr
							{
								return
									player_.create_buffer(
										*_file
									);
							}
						);
				}
			),
			[](
				sge::audio::buffer_unique_ptr const &_buffer
			)
			-> sge::audio::buffer &
			{
				return
					*_buffer;
			}
		);
}
