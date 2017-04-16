#include <sanguis/collision/impl/dir.hpp>
#include <sanguis/collision/impl/line_segment.hpp>
#include <sanguis/collision/impl/pos.hpp>


sanguis::collision::impl::line_segment::line_segment(
	sanguis::collision::impl::pos const &_pos,
	sanguis::collision::impl::dir const &_dir
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

sanguis::collision::impl::pos const &
sanguis::collision::impl::line_segment::pos() const
{
	return
		pos_;
}

sanguis::collision::impl::dir const &
sanguis::collision::impl::line_segment::dir() const
{
	return
		dir_;
}
