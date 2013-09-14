#include <sanguis/collision/aux_/dir.hpp>
#include <sanguis/collision/aux_/line_segment.hpp>
#include <sanguis/collision/aux_/pos.hpp>


sanguis::collision::aux_::line_segment::line_segment(
	sanguis::collision::aux_::pos const &_pos,
	sanguis::collision::aux_::dir const &_dir
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

sanguis::collision::aux_::pos const &
sanguis::collision::aux_::line_segment::pos() const
{
	return
		pos_;
}

sanguis::collision::aux_::dir const &
sanguis::collision::aux_::line_segment::dir() const
{
	return
		dir_;
}
