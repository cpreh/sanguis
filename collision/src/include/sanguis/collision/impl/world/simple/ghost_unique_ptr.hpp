#ifndef SANGUIS_COLLISION_IMPL_WORLD_SIMPLE_GHOST_UNIQUE_PTR_HPP_INCLUDED
#define SANGUIS_COLLISION_IMPL_WORLD_SIMPLE_GHOST_UNIQUE_PTR_HPP_INCLUDED

#include <sanguis/collision/impl/world/simple/ghost_fwd.hpp>
#include <fcppt/unique_ptr_impl.hpp>


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

typedef
fcppt::unique_ptr<
	sanguis::collision::impl::world::simple::ghost
>
ghost_unique_ptr;

}
}
}
}
}

#endif
