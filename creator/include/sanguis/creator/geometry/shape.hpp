#ifndef SANGUIS_CREATOR_GEOMETRY_SHAPE_HPP_INCLUDED
#define SANGUIS_CREATOR_GEOMETRY_SHAPE_HPP_INCLUDED

#include <sanguis/creator/symbol.hpp>
#include <sanguis/creator/geometry/depth.hpp>
#include <sanguis/creator/geometry/polygon.hpp>
#include <sanguis/creator/geometry/shape_fwd.hpp>
#include <sanguis/creator/geometry/solidity.hpp>
#include <sanguis/creator/geometry/texture_name.hpp>
#include <sanguis/creator/geometry/vertex.hpp>


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
		sanguis::creator::geometry::polygon const &,
		sanguis::creator::geometry::solidity,
		sanguis::creator::geometry::depth,
		sanguis::creator::geometry::texture_name const &
	);

	SANGUIS_CREATOR_SYMBOL
	sanguis::creator::geometry::polygon const &
	polygon() const;

	SANGUIS_CREATOR_SYMBOL
	sanguis::creator::geometry::solidity
	solidity() const;

	SANGUIS_CREATOR_SYMBOL
	sanguis::creator::geometry::depth const
	depth() const;

	SANGUIS_CREATOR_SYMBOL
	sanguis::creator::geometry::texture_name const &
	texture_name() const;
private:
	sanguis::creator::geometry::polygon polygon_;

	sanguis::creator::geometry::solidity solidity_;

	sanguis::creator::geometry::depth depth_;

	sanguis::creator::geometry::texture_name texture_name_;
};

}
}
}

#endif
