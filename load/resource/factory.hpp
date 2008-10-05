#ifndef SANGUIS_DRAW_RESOURCE_FACTORY_HPP_INCLUDED
#define SANGUIS_DRAW_RESOURCE_FACTORY_HPP_INCLUDED

#include <sge/string.hpp>
#include <sge/path.hpp>
#include <sge/sprite/animation_series.hpp>
#include <sge/texture/part_fwd.hpp>
#include <sge/renderer/device_fwd.hpp>
#include <sge/image/loader_fwd.hpp>
#include <sge/audio/sound_fwd.hpp>
#include <boost/noncopyable.hpp>

namespace sanguis
{
namespace load
{
namespace resource
{

typedef sge::string identifier_type;

sge::sprite::animation_series const
animation(
	sge::path const &);

sge::texture::part_ptr const
texture(
	identifier_type const &);

sge::audio::sound_ptr const 
sound(
	sge::path const &);
}
}
}

#endif
