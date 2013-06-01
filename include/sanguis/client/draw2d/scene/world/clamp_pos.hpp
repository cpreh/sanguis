#ifndef SANGUIS_CLIENT_DRAW2D_SCENE_WORLD_CLAMP_POS_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_SCENE_WORLD_CLAMP_POS_HPP_INCLUDED

#include <sanguis/client/draw2d/scene/world/signed_pos_fwd.hpp>
#include <sanguis/client/draw2d/scene/world/unsigned_pos_fwd.hpp>


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

sanguis::client::draw2d::scene::world::unsigned_pos const
clamp_pos(
	sanguis::client::draw2d::scene::world::signed_pos const &,
	// TODO: This should be a different type
	sanguis::client::draw2d::scene::world::unsigned_pos const &
);

}
}
}
}
}

#endif
