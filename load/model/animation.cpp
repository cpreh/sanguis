#include "animation.hpp"
#include "../resource/factory.hpp"

sanguis::load::model::animation::animation(
	sge::path const& path)
: path(path)
{}

sge::audio::sound_ptr const sanguis::load::model::animation::start_sound() const
{
	return resource::sound(path/SGE_TEXT("start"));
}

sge::audio::sound_ptr const sanguis::load::model::animation::running_sound() const
{
	return resource::sound(path/SGE_TEXT("running"));
}

sge::audio::sound_ptr const sanguis::load::model::animation::end_sound() const
{
	return resource::sound(path/SGE_TEXT("end"));
}

sge::sprite::animation_series const&
sanguis::load::model::animation::get() const
{
	if(!anim)
		anim.reset(
			new sge::sprite::animation_series(
				resource::animation(path)));
	
	return *anim;
}
