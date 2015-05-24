#include <sanguis/client/load/resource/context.hpp>
#include <sanguis/client/load/resource/sounds.hpp>
#include <sanguis/client/load/resource/textures.hpp>
#include <sge/audio/loader_fwd.hpp>
#include <sge/audio/player_fwd.hpp>
#include <sge/image2d/system_fwd.hpp>
#include <sge/renderer/device/core_fwd.hpp>
#include <fcppt/make_unique_ptr_fcppt.hpp>


sanguis::client::load::resource::textures const &
sanguis::client::load::resource::context::textures() const
{
	return
		*textures_;
}

sanguis::client::load::resource::sounds const &
sanguis::client::load::resource::context::sounds() const
{
	return
		*sounds_;
}

sanguis::client::load::resource::context::context(
	sge::renderer::device::core &_renderer,
	sge::image2d::system &_image_loader,
	sge::audio::loader &_audio_loader,
	sge::audio::player &_audio_player
)
:
	textures_(
		fcppt::make_unique_ptr_fcppt<
			sanguis::client::load::resource::textures
		>(
			_renderer,
			_image_loader
		)
	),
	sounds_(
		fcppt::make_unique_ptr_fcppt<
			sanguis::client::load::resource::sounds
		>(
			_audio_loader,
			_audio_player
		)
	)
{
}

sanguis::client::load::resource::context::~context()
{
}
