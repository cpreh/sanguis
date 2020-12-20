#ifndef SANGUIS_CLIENT_DRAW2D_SCENE_WORLD_BASE_UNIQUE_PTR_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_SCENE_WORLD_BASE_UNIQUE_PTR_HPP_INCLUDED

#include <sanguis/client/draw2d/scene/world/base_fwd.hpp>
#include <fcppt/unique_ptr_impl.hpp>


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

using
base_unique_ptr
=
fcppt::unique_ptr<
	sanguis::client::draw2d::scene::world::base
>;

}
}
}
}
}

#endif
