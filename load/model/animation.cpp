#include "animation.hpp"
#include "../resource/factory.hpp"

sanguis::load::model::animation::animation(
	sge::path const& path)
: path(path)
{}

sge::sprite::animation_series const&
sanguis::load::model::animation::get() const
{
	if(!anim)
		anim.reset(
			new sge::sprite::animation_series(
				resource::animation(path)));
	
	return *anim;
}
