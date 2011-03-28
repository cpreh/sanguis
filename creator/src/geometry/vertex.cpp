#include <sanguis/creator/geometry/vertex.hpp>

sanguis::creator::geometry::vertex::vertex(
	geometry::vector const &_pos,
	geometry::texture_point const &_texcoords
)
:
	pos_(_pos),
	texcoords_(_texcoords)
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
