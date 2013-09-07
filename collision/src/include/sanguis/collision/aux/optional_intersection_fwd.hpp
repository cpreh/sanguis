#ifndef SANGUIS_COLLISION_AUX_OPTIONAL_INTERSECTION_FWD_HPP_INCLUDED
#define SANGUIS_COLLISION_AUX_OPTIONAL_INTERSECTION_FWD_HPP_INCLUDED

#include <sanguis/collision/aux/intersection_fwd.hpp>
#include <fcppt/optional_fwd.hpp>


namespace sanguis
{
namespace collision
{
namespace aux
{

typedef
fcppt::optional<
	sanguis::collision::aux::intersection
> optional_intersection;

}
}
}

#endif
