#include <sanguis/collision/line_segment.hpp>
#include <sanguis/collision/vector2.hpp>


sanguis::collision::line_segment::line_segment(
	sanguis::collision::vector2 const &_pos,
	sanguis::collision::vector2 const &_dir
)
:
	pos_(
		_pos
	),
	dir_(
		_dir
	)
{
}

sanguis::collision::vector2 const &
sanguis::collision::line_segment::pos() const
{
	return
		pos_;
}

sanguis::collision::vector2 const &
sanguis::collision::line_segment::dir() const
{
	return
		dir_;
}
