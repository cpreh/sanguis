#include <sanguis/collision/impl/dir.hpp>
#include <sanguis/collision/impl/line_segment.hpp>
#include <sanguis/collision/impl/pos.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


sanguis::collision::impl::line_segment::line_segment(
	sanguis::collision::impl::pos _pos,
	sanguis::collision::impl::dir _dir
)
:
	pos_(
		std::move(
			_pos
		)
	),
	dir_(
		std::move(
			_dir
		)
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
