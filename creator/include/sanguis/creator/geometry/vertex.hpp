#ifndef SANGUIS_CREATOR_GEOMETRY_VERTEX_HPP_INCLUDED
#define SANGUIS_CREATOR_GEOMETRY_VERTEX_HPP_INCLUDED

#include <sanguis/creator/symbol.hpp>
#include <sanguis/creator/geometry/vertex_fwd.hpp>
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
	SANGUIS_CREATOR_SYMBOL
	vertex(
		sanguis::creator::geometry::vector const &,
		sanguis::creator::geometry::texture_point const &
	);

	SANGUIS_CREATOR_SYMBOL
	sanguis::creator::geometry::vector const &
	pos() const;

	SANGUIS_CREATOR_SYMBOL
	sanguis::creator::geometry::texture_point const &
	texcoords() const;
private:
	sanguis::creator::geometry::vector pos_;

	sanguis::creator::geometry::texture_point texcoords_;
};

}
}
}

#endif
