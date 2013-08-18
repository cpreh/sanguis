#include <sanguis/load/resource/animations.hpp>
#include <sanguis/load/resource/context.hpp>
#include <sanguis/load/resource/sounds.hpp>
#include <sanguis/load/resource/textures.hpp>
#include <sge/audio/loader_fwd.hpp>
#include <sge/audio/player_fwd.hpp>
#include <sge/image2d/system_fwd.hpp>
#include <sge/renderer/device/core_fwd.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/scoped_ptr_impl.hpp>


sanguis::load::resource::textures const &
sanguis::load::resource::context::textures() const
{
	return *textures_;
}

sanguis::load::resource::animations const &
sanguis::load::resource::context::animations() const
{
	return *animations_;
}

sanguis::load::resource::sounds const &
sanguis::load::resource::context::sounds() const
{
	return *sounds_;
}

sanguis::load::resource::context::context(
	sge::renderer::device::core &_renderer,
	sge::image2d::system &_image_loader,
	sge::audio::loader &_audio_loader,
	sge::audio::player &_audio_player
)
:
	textures_(
		fcppt::make_unique_ptr<
			sanguis::load::resource::textures
		>(
			_renderer,
			_image_loader
		)
	),
	animations_(
		fcppt::make_unique_ptr<
			sanguis::load::resource::animations
		>(
			*textures_
		)
	),
	sounds_(
		fcppt::make_unique_ptr<
			sanguis::load::resource::sounds
		>(
			_audio_loader,
			_audio_player
		)
	)
{
}

sanguis::load::resource::context::~context()
{
}
