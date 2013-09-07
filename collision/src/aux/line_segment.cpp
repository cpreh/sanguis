#include <sanguis/collision/aux/dir.hpp>
#include <sanguis/collision/aux/line_segment.hpp>
#include <sanguis/collision/aux/pos.hpp>


sanguis::collision::aux::line_segment::line_segment(
	sanguis::collision::aux::pos const &_pos,
	sanguis::collision::aux::dir const &_dir
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

sanguis::collision::aux::pos const &
sanguis::collision::aux::line_segment::pos() const
{
	return
		pos_;
}

sanguis::collision::aux::dir const &
sanguis::collision::aux::line_segment::dir() const
{
	return
		dir_;
}
