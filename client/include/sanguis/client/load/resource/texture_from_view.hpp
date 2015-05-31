#ifndef SANGUIS_CLIENT_LOAD_RESOURCE_TEXTURE_FROM_VIEW_HPP_INCLUDED
#define SANGUIS_CLIENT_LOAD_RESOURCE_TEXTURE_FROM_VIEW_HPP_INCLUDED

#include <sge/image2d/view/const_object_fwd.hpp>
#include <sge/renderer/device/core_fwd.hpp>
#include <sge/texture/const_part_unique_ptr.hpp>


namespace sanguis
{
namespace client
{
namespace load
{
namespace resource
{

sge::texture::const_part_unique_ptr
texture_from_view(
	sge::renderer::device::core &,
	sge::image2d::view::const_object const &
);

}
}
}
}

#endif
