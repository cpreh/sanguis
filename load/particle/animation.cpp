#include "animation.hpp"
#include "../resource/context.hpp"
#include "../resource/animations.hpp"
#include <sge/make_shared_ptr.hpp>

sanguis::load::particle::animation::animation(
	sge::path const &path,
	resource::context const &ctx)
:
	path(path),
	ctx(ctx)
{}

sge::sprite::animation_series const &
sanguis::load::particle::animation::get() const
{
	if(!anim)
		anim = sge::make_shared_ptr<
				sge::sprite::animation_series
			>(
				ctx.animations().load(path));
	
	return *anim;
}
