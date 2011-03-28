#include <sanguis/creator/generator/result.hpp>

sanguis::creator::generator::result::result(
	geometry::shape_container const &_shapes
)
:
	shapes_(_shapes)
{
}

sanguis::creator::geometry::shape_container const &
sanguis::creator::generator::result::shapes() const
{
	return shapes_;
}
