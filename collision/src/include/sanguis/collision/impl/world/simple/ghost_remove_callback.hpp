#ifndef SANGUIS_COLLISION_IMPL_WORLD_SIMPLE_GHOST_REMOVE_CALLBACK_HPP_INCLUDED
#define SANGUIS_COLLISION_IMPL_WORLD_SIMPLE_GHOST_REMOVE_CALLBACK_HPP_INCLUDED

#include <sanguis/collision/impl/world/simple/ghost_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <functional>
#include <fcppt/config/external_end.hpp>


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
std::function<
	void (
		sanguis::collision::impl::world::simple::ghost &
	)
>
ghost_remove_callback;

}
}
}
}
}

#endif
