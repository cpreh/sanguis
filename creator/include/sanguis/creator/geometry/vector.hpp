#ifndef SANGUIS_CREATOR_GEOMETRY_VECTOR_HPP_INCLUDED
#define SANGUIS_CREATOR_GEOMETRY_VECTOR_HPP_INCLUDED

#include <sanguis/creator/geometry/unit.hpp>
#include <fcppt/math/vector/static.hpp>

namespace sanguis
{
namespace creator
{
namespace geometry
{

typedef fcppt::math::vector::static_<
	geometry::unit,
	2
>::type vector;

}
}
}

#endif
