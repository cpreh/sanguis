#ifndef SANGUIS_CREATOR_GEOMETRY_POLYGON_HPP_INCLUDED
#define SANGUIS_CREATOR_GEOMETRY_POLYGON_HPP_INCLUDED

#include <sanguis/creator/geometry/vertex.hpp>
#include <fcppt/config/external_begin.hpp>
#include <vector>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace creator
{
namespace geometry
{

typedef std::vector<
	sanguis::creator::geometry::vertex
> polygon;

}
}
}

#endif
