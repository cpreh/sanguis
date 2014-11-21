#ifndef SANGUIS_CLIENT_DRAW2D_SCENE_WORLD_CREATE_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_SCENE_WORLD_CREATE_HPP_INCLUDED

#include <sanguis/client/draw2d/scene/world/base_unique_ptr.hpp>
#include <sanguis/client/draw2d/scene/world/parameters_fwd.hpp>
#include <sanguis/creator/name_fwd.hpp>


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

sanguis::client::draw2d::scene::world::base_unique_ptr
create(
	sanguis::creator::name const &,
	sanguis::client::draw2d::scene::world::parameters const &
);

}
}
}
}
}

#endif
