#include "factory.hpp"
#include "environment.hpp"
#include "../../exception.hpp"

namespace
{
environment &get_env()
{
	if (!sanguis::load::resource::global_env())
		throw exception(SGE_TEXT("no resource connection found"));
	return *sanguis::load::resource::global_env();
}
}

sge::sprite::animation_series const 
sanguis::load::resource::animation(sge::path const& path)
{
	return get_env().load_animation(path);
}

sge::audio::sound_ptr const
sanguis::load::resource::sound(sge::path const &p)
{
	return get_env().load_sound(path);
}

const sge::texture::part_ptr
sanguis::load::resource::texture(identifier_type const& id)
{
	return get_env().load_texture(id);
}
