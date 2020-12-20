#include <sanguis/client/load/resource/context.hpp>
#include <sanguis/client/load/resource/sounds.hpp>
#include <sanguis/client/load/resource/textures.hpp>
#include <sge/audio/loader_ref.hpp>
#include <sge/audio/player_ref.hpp>
#include <sge/image2d/system_ref.hpp>
#include <sge/renderer/device/core_ref.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/log/context_reference.hpp>


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
	fcppt::log::context_reference const _log_context,
	sge::renderer::device::core_ref const _renderer,
	sge::image2d::system_ref const _image_loader,
	sge::audio::loader_ref const _audio_loader,
	sge::audio::player_ref const _audio_player
)
:
	textures_(
		fcppt::make_unique_ptr<
			sanguis::client::load::resource::textures
		>(
			_log_context,
			_renderer,
			_image_loader
		)
	),
	sounds_(
		fcppt::make_unique_ptr<
			sanguis::client::load::resource::sounds
		>(
			_audio_loader.get(),
			_audio_player.get()
		)
	)
{
}

sanguis::client::load::resource::context::~context()
= default;
