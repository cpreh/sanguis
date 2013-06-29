#include <sanguis/collision/merge_intersection.hpp>
#include <sanguis/collision/intersection_pair.hpp>
#include <sanguis/collision/optional_intersection.hpp>


sanguis::collision::intersection_pair::intersection_pair()
:
	first_(),
	second_()
{
}

sanguis::collision::intersection_pair::intersection_pair(
	sanguis::collision::optional_intersection const &_first,
	sanguis::collision::optional_intersection const &_second
)
:
	first_(
		_first
	),
	second_(
		_second
	)
{
}

void
sanguis::collision::intersection_pair::merge(
	intersection_pair const &_other
)
{
	first_ =
		sanguis::collision::merge_intersection(
			first_,
			_other.first()
		);

	second_ =
		sanguis::collision::merge_intersection(
			second_,
			_other.second()
		);
}

sanguis::collision::optional_intersection const &
sanguis::collision::intersection_pair::first() const
{
	return
		first_;
}

sanguis::collision::optional_intersection const &
sanguis::collision::intersection_pair::second() const
{
	return
		second_;
}
