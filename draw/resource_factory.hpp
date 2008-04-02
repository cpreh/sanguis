#ifndef SANGUIS_DRAW_RESOURCE_FACTORY_HPP_INCLUDED
#define SANGUIS_DRAW_RESOURCE_FACTORY_HPP_INCLUDED

#include <sge/string.hpp>
#include <sge/sprite/texture_animation.hpp>
#include <sge/texture/virtual_texture.hpp>
#include <sge/renderer/renderer.hpp>
#include <sge/image/image_loader.hpp>
#include <boost/noncopyable.hpp>

namespace sanguis
{
namespace draw
{
namespace resource
{

typedef sge::string identifier_type;

const sge::sprite::texture_animation::animation_series animation(const identifier_type&);
const sge::virtual_texture_ptr texture(const identifier_type&);

struct connection : boost::noncopyable
{
	connection(const sge::image_loader_ptr,const sge::renderer_ptr);
	~connection();
};

}
}
}

#endif
