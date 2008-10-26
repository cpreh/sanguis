#include "animation.hpp"
#include "animation_sound.hpp"
#include "../resource/factory.hpp"

sanguis::load::model::animation::animation(
	sge::path const &path)
:
	path(path)
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

sanguis::load::model::animation_sound const &
sanguis::load::model::animation::sounds() const
{
	if(!sounds_)
		sounds_.reset(
			new animation_sound(
				path));
	return *sounds_;
}
