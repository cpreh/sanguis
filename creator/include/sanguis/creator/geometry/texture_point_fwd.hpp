#ifndef SANGUIS_CREATOR_GEOMETRY_TEXTURE_POINT_FWD_HPP_INCLUDED
#define SANGUIS_CREATOR_GEOMETRY_TEXTURE_POINT_FWD_HPP_INCLUDED

#include <sanguis/creator/geometry/texture_unit.hpp>
#include <fcppt/math/vector/static.hpp>


namespace sanguis
{
namespace creator
{
namespace geometry
{

typedef fcppt::math::vector::static_<
	sanguis::creator::geometry::texture_unit,
	2
>::type texture_point;

}
}
}

#endif
