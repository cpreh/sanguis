#include "factory.hpp"
#include "environment.hpp"
#include "../../exception.hpp"

namespace
{
sanguis::load::resource::environment &get_env()
{
	if (!sanguis::load::resource::global_env())
		throw sanguis::exception(SGE_TEXT("no resource connection found"));
	return *sanguis::load::resource::global_env();
}
}

sge::sprite::animation_series const 
sanguis::load::resource::animation(
	sge::path const &path)
{
	return get_env().load_animation(path);
}

sanguis::load::sound_collection const &
sanguis::load::resource::sound(
	sge::path const &p)
{
	return get_env().load_sound(p);
}

sge::texture::part_ptr const
sanguis::load::resource::texture(
	identifier_type const &id)
{
	return get_env().load_texture(id);
}

sge::audio::sound_ptr const
sanguis::load::resource::make_sound(
	sge::audio::file_ptr const f)
{
	return get_env().make_sound(f);
}
