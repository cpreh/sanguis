#ifndef SANGUIS_CREATOR_GEOMETRY_SHAPE_HPP_INCLUDED
#define SANGUIS_CREATOR_GEOMETRY_SHAPE_HPP_INCLUDED

#include <sanguis/creator/geometry/shape_fwd.hpp>
#include <sanguis/creator/geometry/polygon.hpp>
#include <sanguis/creator/geometry/solidity.hpp>
#include <sanguis/creator/geometry/texture_name.hpp>
#include <vector>

namespace sanguis
{
namespace creator
{
namespace geometry
{

class shape
{
public:
	shape(
		geometry::polygon const &,
		geometry::solidity::type,
		geometry::texture_name const &
	);
};

}
}
}

#endif
