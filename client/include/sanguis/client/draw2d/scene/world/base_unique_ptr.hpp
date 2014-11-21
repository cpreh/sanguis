#ifndef SANGUIS_CLIENT_DRAW2D_SCENE_WORLD_BASE_UNIQUE_PTR_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_SCENE_WORLD_BASE_UNIQUE_PTR_HPP_INCLUDED

#include <sanguis/client/draw2d/scene/world/base_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <memory>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace client
{
namespace draw2d
{
namespace scene
{
namespace world
{

typedef
std::unique_ptr<
	sanguis::client::draw2d::scene::world::base
>
base_unique_ptr;

}
}
}
}
}

#endif
