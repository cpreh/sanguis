#ifndef SANGUIS_COLLISION_IMPL_WORLD_SIMPLE_GHOST_REMOVE_CALLBACK_HPP_INCLUDED
#define SANGUIS_COLLISION_IMPL_WORLD_SIMPLE_GHOST_REMOVE_CALLBACK_HPP_INCLUDED

#include <sanguis/collision/impl/world/simple/ghost_fwd.hpp>
#include <fcppt/function_impl.hpp>


namespace sanguis::collision::impl::world::simple
{

using
ghost_remove_callback
=
fcppt::function<
	void (
		sanguis::collision::impl::world::simple::ghost &
	)
>;

}

#endif
