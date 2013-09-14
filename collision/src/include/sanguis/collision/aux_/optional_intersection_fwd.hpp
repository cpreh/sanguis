#ifndef SANGUIS_COLLISION_AUX__OPTIONAL_INTERSECTION_FWD_HPP_INCLUDED
#define SANGUIS_COLLISION_AUX__OPTIONAL_INTERSECTION_FWD_HPP_INCLUDED

#include <sanguis/collision/aux_/intersection_fwd.hpp>
#include <fcppt/optional_fwd.hpp>


namespace sanguis
{
namespace collision
{
namespace aux_
{

typedef
fcppt::optional<
	sanguis::collision::aux_::intersection
> optional_intersection;

}
}
}

#endif
