#ifndef SANGUIS_DRAW_RESOURCE_FACTORY_HPP_INCLUDED
#define SANGUIS_DRAW_RESOURCE_FACTORY_HPP_INCLUDED

#include <sge/string.hpp>
#include <sge/sprite/animation_series.hpp>
#include <sge/texture/part.hpp>
#include <sge/renderer/device.hpp>
#include <sge/image/loader.hpp>
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

struct connection : boost::noncopyable
{
	connection(
		sge::image::loader_ptr,
		sge::renderer::device_ptr);
	~connection();
};

}
}
}

#endif
