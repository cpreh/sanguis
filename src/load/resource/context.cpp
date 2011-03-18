#include "context.hpp"
#include "textures.hpp"
#include "sounds.hpp"
#include "animations.hpp"
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/ref.hpp>

sanguis::load::resource::textures const &
sanguis::load::resource::context::textures() const
{
	return *textures_;
}

sanguis::load::resource::sounds const &
sanguis::load::resource::context::sounds() const
{
	return *sounds_;
}

sanguis::load::resource::animations const &
sanguis::load::resource::context::animations() const
{
	return *animations_;
}

void
sanguis::load::resource::context::update(
	time_type const delta
) const
{
	textures_->cleanup(
		delta
	);
}

sanguis::load::resource::context::context(
	sge::renderer::device_ptr const _renderer,
	sge::image2d::multi_loader &_image_loader,
	sge::audio::multi_loader &_audio_loader,
	sge::audio::player_ptr const _audio_player,
	sge::audio::pool &_audio_pool
)
:
	textures_(
		fcppt::make_unique_ptr<
			resource::textures
		>(
			_renderer,
			fcppt::ref(
				_image_loader
			)
		)
	),
	sounds_(
		fcppt::make_unique_ptr<
			resource::sounds
		>(
			fcppt::ref(
				_audio_loader
			),
			_audio_player,
			fcppt::ref(
				_audio_pool
			)
		)
	),
	animations_(
		fcppt::make_unique_ptr<
			resource::animations
		>(
			fcppt::ref(
				*textures_
			)
		)
	)
{}

sanguis::load::resource::context::~context()
{}
