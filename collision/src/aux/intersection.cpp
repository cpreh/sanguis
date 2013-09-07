#include <sanguis/collision/aux/dir.hpp>
#include <sanguis/collision/aux/intersection.hpp>


sanguis::collision::aux::intersection::intersection(
	sanguis::collision::aux::dir const &_dir
)
:
	dir_(
		_dir
	)
{
}

sanguis::collision::aux::dir const &
sanguis::collision::aux::intersection::dir() const
{
	return
		dir_;
}
