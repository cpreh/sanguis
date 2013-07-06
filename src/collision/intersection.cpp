#include <sanguis/collision/dir.hpp>
#include <sanguis/collision/intersection.hpp>


sanguis::collision::intersection::intersection(
	sanguis::collision::dir const &_dir
)
:
	dir_(
		_dir
	)
{
}

sanguis::collision::dir const &
sanguis::collision::intersection::dir() const
{
	return
		dir_;
}
