#ifndef SANGUIS_CREATOR_GEOMETRY_VERTEX_HPP_INCLUDED
#define SANGUIS_CREATOR_GEOMETRY_VERTEX_HPP_INCLUDED

#include <sanguis/creator/geometry/vertex_fwd.hpp>
#include <sanguis/creator/geometry/vector.hpp>
#include <sanguis/creator/geometry/texture_point.hpp>
#include <sanguis/creator/symbol.hpp>
#include <fcppt/math/vector/object_impl.hpp>

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
		geometry::vector const &,
		geometry::texture_point const &
	);

	SANGUIS_CREATOR_SYMBOL
	geometry::vector const &
	pos() const;

	SANGUIS_CREATOR_SYMBOL
	geometry::texture_point const &
	texcoords() const;
private:
	geometry::vector pos_;

	geometry::texture_point texcoords_;
};

}
}
}

#endif
