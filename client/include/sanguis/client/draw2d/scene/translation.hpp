#ifndef SANGUIS_CLIENT_DRAW2D_SCENE_TRANSLATION_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_SCENE_TRANSLATION_HPP_INCLUDED

#include <sanguis/client/draw2d/player_center_fwd.hpp>
#include <sanguis/client/draw2d/translation_fwd.hpp>
#include <sge/renderer/screen_size_fwd.hpp>


namespace sanguis
{
namespace client
{
namespace draw2d
{
namespace scene
{

sanguis::client::draw2d::translation
translation(
	sanguis::client::draw2d::player_center,
	sge::renderer::screen_size
);

}
}
}
}

#endif

