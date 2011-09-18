#include <sanguis/client/draw2d/scene/world/sort_shapes.hpp>
#include <sanguis/creator/geometry/shape.hpp>

bool
sanguis::client::draw2d::scene::world::sort_shapes(
	sanguis::creator::geometry::shape const &_left,
	sanguis::creator::geometry::shape const &_right
)
{
	return
		_left.depth()
		!= _right.depth()
		?
			_left.depth()
			< _right.depth()
		:
			_left.texture_name()
			< _right.texture_name();
}
