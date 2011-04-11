#ifndef SANGUIS_CLIENT_DRAW2D_SCENE_SCREEN_CENTER_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_SCENE_SCREEN_CENTER_HPP_INCLUDED

#include "../sprite/center.hpp"
#include "../vector2.hpp"
#include <sge/renderer/screen_size.hpp>

namespace sanguis
{
namespace client
{
namespace draw2d
{
namespace scene
{

draw2d::vector2 const
screen_center(
	sprite::center const &player_center,
	sge::renderer::screen_size const &
);

}
}
}
}

#endif

