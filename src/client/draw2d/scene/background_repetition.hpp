#ifndef SANGUIS_CLIENT_DRAW2D_SCENE_BACKGROUND_REPETITION_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_SCENE_BACKGROUND_REPETITION_HPP_INCLUDED

#include "../funit.hpp"
#include <sge/renderer/device_ptr.hpp>
#include <sge/texture/const_part_ptr.hpp>

namespace sanguis
{
namespace client
{
namespace draw2d
{
namespace scene
{

draw2d::funit
background_repetition(
	sge::renderer::device_ptr,
	sge::texture::const_part_ptr
);

}
}
}
}

#endif