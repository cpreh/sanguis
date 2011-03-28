#ifndef SANGUIS_CREATOR_GEOMETRY_RECT_HPP_INCLUDED
#define SANGUIS_CREATOR_GEOMETRY_RECT_HPP_INCLUDED

#include <sanguis/creator/geometry/unit.hpp>
#include <fcppt/math/box/rect.hpp>

namespace sanguis
{
namespace creator
{
namespace geometry
{

typedef fcppt::math::box::rect<
	geometry::unit
>::type rect;

}
}
}

#endif
