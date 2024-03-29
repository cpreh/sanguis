#ifndef SANGUIS_CLIENT_LOAD_RESOURCE_MAKE_MISSING_TEXTURE_HPP_INCLUDED
#define SANGUIS_CLIENT_LOAD_RESOURCE_MAKE_MISSING_TEXTURE_HPP_INCLUDED

#include <sge/image/size_type.hpp>
#include <sge/image/color/any/object_fwd.hpp>
#include <sge/renderer/device/core_ref.hpp>
#include <sge/texture/const_part_unique_ptr.hpp>

namespace sanguis::client::load::resource
{

sge::texture::const_part_unique_ptr make_missing_texture(
    sge::renderer::device::core_ref,
    sge::image::size_type,
    sge::image::color::any::object const &,
    sge::image::color::any::object const &);

}

#endif
