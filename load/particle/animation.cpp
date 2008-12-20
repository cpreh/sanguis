#include "animation.hpp"
#include "../resource/factory.hpp"
#include <sge/make_shared_ptr.hpp>

sanguis::load::particle::animation::animation(
	sge::path const &path)
:
	path(path)
{}

sge::sprite::animation_series const &
sanguis::load::particle::animation::get() const
{
	if(!anim)
		anim = sge::make_shared_ptr<
				sge::sprite::animation_series
			>(
				resource::animation(path));
	
	return *anim;
}
