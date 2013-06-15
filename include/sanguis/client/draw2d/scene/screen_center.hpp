#ifndef SANGUIS_CLIENT_DRAW2D_SCENE_SCREEN_CENTER_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_SCENE_SCREEN_CENTER_HPP_INCLUDED

#include <sanguis/client/draw2d/vector2_fwd.hpp>
#include <sanguis/client/draw2d/sprite/center_fwd.hpp>
#include <sge/renderer/screen_size_fwd.hpp>


namespace sanguis
{
namespace client
{
namespace draw2d
{
namespace scene
{

sanguis::client::draw2d::vector2 const
screen_center(
	sanguis::client::draw2d::sprite::center player_center,
	sge::renderer::screen_size
);

}
}
}
}

#endif

