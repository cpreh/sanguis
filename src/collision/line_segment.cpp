#include <sanguis/collision/dir.hpp>
#include <sanguis/collision/line_segment.hpp>
#include <sanguis/collision/pos.hpp>


sanguis::collision::line_segment::line_segment(
	sanguis::collision::pos const &_pos,
	sanguis::collision::dir const &_dir
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

sanguis::collision::pos const &
sanguis::collision::line_segment::pos() const
{
	return
		pos_;
}

sanguis::collision::dir const &
sanguis::collision::line_segment::dir() const
{
	return
		dir_;
}
