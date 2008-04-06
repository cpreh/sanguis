#include "animation.hpp"

sanguis::load::model::animation::animation(
	sge::path const& path)
: path(path)
{}

sge::sprite::texture_animation const&
sanguis::load::model::animation::get() const
{
	//if(!anim)
	//	anim.reset(resource::animation());
	return *anim;
}
