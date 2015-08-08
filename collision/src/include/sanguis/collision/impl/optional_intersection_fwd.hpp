#ifndef SANGUIS_COLLISION_IMPL_OPTIONAL_INTERSECTION_FWD_HPP_INCLUDED
#define SANGUIS_COLLISION_IMPL_OPTIONAL_INTERSECTION_FWD_HPP_INCLUDED

#include <sanguis/collision/impl/intersection_fwd.hpp>
#include <fcppt/optional_fwd.hpp>


namespace sanguis
{
namespace collision
{
namespace impl
{

typedef
fcppt::optional<
	sanguis::collision::impl::intersection
>
optional_intersection;

}
}
}

#endif
