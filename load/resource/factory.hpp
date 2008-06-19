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

const sge::sprite::animation_series animation(
	sge::path const&);
const sge::texture::part_ptr texture(const identifier_type&);

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
