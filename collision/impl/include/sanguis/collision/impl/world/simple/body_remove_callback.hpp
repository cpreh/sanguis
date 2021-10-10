#ifndef SANGUIS_COLLISION_IMPL_WORLD_SIMPLE_BODY_REMOVE_CALLBACK_HPP_INCLUDED
#define SANGUIS_COLLISION_IMPL_WORLD_SIMPLE_BODY_REMOVE_CALLBACK_HPP_INCLUDED

#include <sanguis/collision/impl/world/simple/body_fwd.hpp>
#include <fcppt/function_impl.hpp>

namespace sanguis::collision::impl::world::simple
{

using body_remove_callback = fcppt::function<void(sanguis::collision::impl::world::simple::body &)>;

}

#endif
