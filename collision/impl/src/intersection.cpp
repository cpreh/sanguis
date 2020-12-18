#include <sanguis/collision/impl/dir.hpp>
#include <sanguis/collision/impl/intersection.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


sanguis::collision::impl::intersection::intersection(
	sanguis::collision::impl::dir _dir
)
:
	dir_(
		std::move(
			_dir
		)
	)
{
}

sanguis::collision::impl::dir const &
sanguis::collision::impl::intersection::dir() const
{
	return
		dir_;
}
