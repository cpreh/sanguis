#ifndef SANGUIS_CREATOR_GEOMETRY_VERTEX_HPP_INCLUDED
#define SANGUIS_CREATOR_GEOMETRY_VERTEX_HPP_INCLUDED

#include <sanguis/creator/geometry/vector.hpp>
#include <sanguis/creator/geometry/texture_point.hpp>

namespace sanguis
{
namespace creator
{
namespace geometry
{

class vertex
{
public:
	vertex(
		geometry::vector const &,
		geometry::texture_point const &
	);
};

}
}
}

#endif
