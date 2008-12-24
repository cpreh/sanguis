#include "animation.hpp"
#include "../resource/context.hpp"
#include "../resource/animations.hpp"
#include <sge/auto_ptr.hpp>
#include <sge/make_auto_ptr.hpp>

sanguis::load::particle::animation::animation(
	sge::path const &path,
	resource::context const &ctx)
:
	path(path),
	ctx(ctx)
{}

sanguis::load::particle::animation::~animation()
{}

sge::sprite::animation_series const &
sanguis::load::particle::animation::get() const
{
	if(!anim)
	{
		sge::auto_ptr<
			sge::sprite::animation_series
		> series(
			sge::make_auto_ptr<
				sge::sprite::animation_series
			>(
				ctx.animations().load(path)));

		anim.take(
			series);
	}
	
	return *anim;
}
