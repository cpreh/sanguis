#include <sanguis/collision/aux_/dir.hpp>
#include <sanguis/collision/aux_/intersection.hpp>


sanguis::collision::aux_::intersection::intersection(
	sanguis::collision::aux_::dir const &_dir
)
:
	dir_(
		_dir
	)
{
}

sanguis::collision::aux_::dir const &
sanguis::collision::aux_::intersection::dir() const
{
	return
		dir_;
}
