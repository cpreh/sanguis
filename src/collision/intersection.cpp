#include <sanguis/collision/dir.hpp>
#include <sanguis/collision/intersection.hpp>
#include <sanguis/collision/unit.hpp>


sanguis::collision::intersection::intersection(
	sanguis::collision::dir const &_dir,
	sanguis::collision::unit const _pos
)
:
	dir_(
		_dir
	),
	pos_(
		_pos
	)
{
}

sanguis::collision::dir const &
sanguis::collision::intersection::dir() const
{
	return
		dir_;
}

sanguis::collision::unit
sanguis::collision::intersection::pos() const
{
	return
		pos_;
}
