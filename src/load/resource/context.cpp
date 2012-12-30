#include <sanguis/load/resource/context.hpp>
#include <sanguis/load/resource/textures.hpp>
#include <sanguis/load/resource/animations.hpp>
#include <fcppt/make_unique_ptr.hpp>

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

sanguis::load::resource::context::context(
	sge::renderer::device::core &_renderer,
	sge::image2d::system &_image_loader
)
:
	textures_(
		fcppt::make_unique_ptr<
			resource::textures
		>(
			_renderer,
			_image_loader
		)
	),
	animations_(
		fcppt::make_unique_ptr<
			resource::animations
		>(
			*textures_
		)
	)
{
}

sanguis::load::resource::context::~context()
{
}
