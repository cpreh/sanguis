#ifndef SANGUIS_COLLISION_IMPL_WORLD_SIMPLE_PUSH_NEAR_HPP_INCLUDED
#define SANGUIS_COLLISION_IMPL_WORLD_SIMPLE_PUSH_NEAR_HPP_INCLUDED

#include <sanguis/collision/optional_result_fwd.hpp>
#include <sanguis/collision/impl/world/simple/body_fwd.hpp>


namespace sanguis
{
namespace collision
{
namespace impl
{
namespace world
{
namespace simple
{

sanguis::collision::optional_result const
push_near(
	sanguis::collision::impl::world::simple::body const &,
	sanguis::collision::impl::world::simple::body const &
);

}
}
}
}
}

#endif
