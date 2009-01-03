#include "animation.hpp"
#include "animation_sound.hpp"
#include "../resource/animations.hpp"
#include "../resource/context.hpp"
#include <sge/make_shared_ptr.hpp>

sanguis::load::model::animation::animation(
	sge::filesystem::path const &path,
	load::resource::context const &ctx)
:
	path(path),
	ctx(ctx)
{}

sge::sprite::animation_series const &
sanguis::load::model::animation::get() const
{
	if(!anim)
		anim = sge::make_shared_ptr<
				sge::sprite::animation_series
			>(
				ctx.animations().load(path));
	
	return *anim;
}

sanguis::load::model::animation_sound const &
sanguis::load::model::animation::sounds() const
{
	if(!sounds_)
		sounds_.reset(
			new animation_sound(
				path,
				ctx));
	return *sounds_;
}
