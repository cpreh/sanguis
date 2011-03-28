#ifndef SANGUIS_CREATOR_GEOMETRY_SHAPE_HPP_INCLUDED
#define SANGUIS_CREATOR_GEOMETRY_SHAPE_HPP_INCLUDED

#include <sanguis/creator/geometry/shape_fwd.hpp>
#include <sanguis/creator/geometry/polygon.hpp>
#include <sanguis/creator/geometry/solidity.hpp>
#include <sanguis/creator/geometry/texture_name.hpp>
#include <sanguis/creator/geometry/vertex.hpp>
#include <sanguis/creator/symbol.hpp>
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
	SANGUIS_CREATOR_SYMBOL
	shape(
		geometry::polygon const &,
		geometry::solidity::type,
		geometry::texture_name const &
	);

	SANGUIS_CREATOR_SYMBOL
	geometry::polygon const &
	polygon() const;

	SANGUIS_CREATOR_SYMBOL
	geometry::solidity::type
	solidity() const;

	SANGUIS_CREATOR_SYMBOL
	geometry::texture_name const &
	texture_name() const;
private:
	geometry::polygon polygon_;

	geometry::solidity::type solidity_;

	geometry::texture_name texture_name_;
};

}
}
}

#endif
