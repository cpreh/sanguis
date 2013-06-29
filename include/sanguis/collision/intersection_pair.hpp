#ifndef SANGUIS_COLLISION_INTERSECTION_PAIR_HPP_INCLUDED
#define SANGUIS_COLLISION_INTERSECTION_PAIR_HPP_INCLUDED

#include <sanguis/collision/intersection_pair_fwd.hpp>
#include <sanguis/collision/optional_intersection.hpp>


namespace sanguis
{
namespace collision
{

class intersection_pair
{
public:
	intersection_pair();

	intersection_pair(
		sanguis::collision::optional_intersection const &,
		sanguis::collision::optional_intersection const &
	);

	void
	merge(
		intersection_pair const &
	);

	sanguis::collision::optional_intersection const &
	first() const;

	sanguis::collision::optional_intersection const &
	second() const;
private:
	sanguis::collision::optional_intersection first_;

	sanguis::collision::optional_intersection second_;
};

}
}

#endif
