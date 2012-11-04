#include <sanguis/creator/geometry/depth.hpp>
#include <sanguis/creator/geometry/polygon.hpp>
#include <sanguis/creator/geometry/shape.hpp>
#include <sanguis/creator/geometry/solidity.hpp>
#include <sanguis/creator/geometry/texture_name.hpp>
#include <sanguis/creator/geometry/vertex.hpp>


sanguis::creator::geometry::shape::shape(
	sanguis::creator::geometry::polygon const &_polygon,
	sanguis::creator::geometry::solidity::type const _solidity,
	sanguis::creator::geometry::depth const _depth,
	sanguis::creator::geometry::texture_name const &_texture_name
)
:
	polygon_(
		_polygon
	),
	solidity_(
		_solidity
	),
	depth_(
		_depth
	),
	texture_name_(
		_texture_name
	)
{
}

sanguis::creator::geometry::polygon const &
sanguis::creator::geometry::shape::polygon() const
{
	return polygon_;
}

sanguis::creator::geometry::solidity::type
sanguis::creator::geometry::shape::solidity() const
{
	return solidity_;
}

sanguis::creator::geometry::depth const
sanguis::creator::geometry::shape::depth() const
{
	return depth_;
}

sanguis::creator::geometry::texture_name const &
sanguis::creator::geometry::shape::texture_name() const
{
	return texture_name_;
}
