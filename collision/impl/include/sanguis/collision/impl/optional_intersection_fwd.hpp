#ifndef SANGUIS_COLLISION_IMPL_OPTIONAL_INTERSECTION_FWD_HPP_INCLUDED
#define SANGUIS_COLLISION_IMPL_OPTIONAL_INTERSECTION_FWD_HPP_INCLUDED

#include <sanguis/collision/impl/intersection_fwd.hpp>
#include <fcppt/optional/object_fwd.hpp>


namespace sanguis::collision::impl
{

using
optional_intersection
=
fcppt::optional::object<
	sanguis::collision::impl::intersection
>;

}

#endif
