#ifndef SANGUIS_DRAW_RESOURCE_FACTORY_HPP_INCLUDED
#define SANGUIS_DRAW_RESOURCE_FACTORY_HPP_INCLUDED

#include <sge/string.hpp>
#include <sge/path.hpp>
#include <sge/sprite/animation_series.hpp> // TODO: fwd this
#include <sge/texture/part_fwd.hpp>
#include <sge/audio/file_fwd.hpp>
#include <sge/audio/sound_fwd.hpp>

namespace sanguis
{
namespace load
{

class sound_collection;

namespace resource
{

typedef sge::string identifier_type;

sge::sprite::animation_series const
animation(
	sge::path const &);

sge::texture::part_ptr const
texture(
	identifier_type const &);

sound_collection const &
sound(
	sge::path const &);

sge::audio::sound_ptr const
make_sound(
	sge::audio::file_ptr);

}
}
}

#endif
