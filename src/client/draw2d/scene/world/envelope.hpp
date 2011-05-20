#ifndef SANGUIS_CLIENT_DRAW2D_SCENE_WORLD_ENVELOPE_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_SCENE_WORLD_ENVELOPE_HPP_INCLUDED

#include <sanguis/creator/geometry/polygon.hpp>
#include <sanguis/creator/geometry/rect.hpp>

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

sanguis::creator::geometry::rect const
envelope(
	sanguis::creator::geometry::polygon const &
);

}
}
}
}
}

#endif
