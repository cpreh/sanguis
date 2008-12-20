#include "context.hpp"
#include "textures.hpp"
#include "sounds.hpp"
#include "animations.hpp"

sanguis::load::resource::textures const &
sanguis::load::resource::context::textures() const
{
	return *textures;
}

sanguis::load::resource::sounds const &
sanguis::load::resource::context::sounds() const
{
	return *sounds;
}

sanguis::load::resource::animations const &
sanguis::load::resource::context::animations() const
{
	return *animations;	
}

sanguis::load::resource::context::context(
	sge::renderer::device_ptr const rend,
	sge::image::loader_ptr const il,
	sge::audio::multi_loader &ml,
	sge::audio::player_ptr const ap,
	sge::audio::pool_ptr const pool)
:
	textures_(
		new resource::textures()),
	sounds_(
		new resource::sounds()),
	animations_(
		new resource::animations())
{}

sanguis::load::resource::context::~context()
{}
