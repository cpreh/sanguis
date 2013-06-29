#ifndef SANGUIS_COLLISION_OPTIONAL_INTERSECTION_FWD_HPP_INCLUDED
#define SANGUIS_COLLISION_OPTIONAL_INTERSECTION_FWD_HPP_INCLUDED

#include <sanguis/collision/intersection_fwd.hpp>
#include <fcppt/optional_fwd.hpp>


namespace sanguis
{
namespace collision
{

typedef
fcppt::optional<
	sanguis::collision::intersection
> optional_intersection;

}
}

#endif
