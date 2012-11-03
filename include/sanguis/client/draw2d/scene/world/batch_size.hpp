#ifndef SANGUIS_CLIENT_DRAW2D_SCENE_WORLD_BATCH_SIZE_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_SCENE_WORLD_BATCH_SIZE_HPP_INCLUDED

#include <sanguis/creator/geometry/unit.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/mpl/integral_c.hpp>
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

typedef boost::mpl::integral_c<
	sanguis::creator::geometry::unit,
	1024
> batch_size;

}
}
}
}
}

#endif
