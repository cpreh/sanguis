#include <sanguis/collision/impl/dir.hpp>
#include <sanguis/collision/impl/intersection.hpp>


sanguis::collision::impl::intersection::intersection(
	sanguis::collision::impl::dir const &_dir
)
:
	dir_(
		_dir
	)
{
}

sanguis::collision::impl::dir const &
sanguis::collision::impl::intersection::dir() const
{
	return
		dir_;
}
