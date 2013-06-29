#ifndef SANGUIS_COLLISION_MERGE_INTERSECTION_HPP_INCLUDED
#define SANGUIS_COLLISION_MERGE_INTERSECTION_HPP_INCLUDED

#include <sanguis/collision/optional_intersection_fwd.hpp>


namespace sanguis
{
namespace collision
{

sanguis::collision::optional_intersection const
merge_intersection(
	sanguis::collision::optional_intersection,
	sanguis::collision::optional_intersection
);

}
}

#endif
