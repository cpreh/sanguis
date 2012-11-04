#include <sanguis/creator/geometry/texture_point.hpp>
#include <sanguis/creator/geometry/vector.hpp>
#include <sanguis/creator/geometry/vertex.hpp>


sanguis::creator::geometry::vertex::vertex(
	sanguis::creator::geometry::vector const &_pos,
	sanguis::creator::geometry::texture_point const &_texcoords
)
:
	pos_(
		_pos
	),
	texcoords_(
		_texcoords
	)
{
}

sanguis::creator::geometry::vector const &
sanguis::creator::geometry::vertex::pos() const
{
	return pos_;
}

sanguis::creator::geometry::texture_point const &
sanguis::creator::geometry::vertex::texcoords() const
{
	return texcoords_;
}
