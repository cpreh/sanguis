#ifndef SANGUIS_COLLISION_IMPL_WORLD_SIMPLE_BODY_MOVE_CALLBACK_HPP_INCLUDED
#define SANGUIS_COLLISION_IMPL_WORLD_SIMPLE_BODY_MOVE_CALLBACK_HPP_INCLUDED

#include <sanguis/collision/impl/world/simple/body_fwd.hpp>
#include <fcppt/function_impl.hpp>
#include <fcppt/reference_fwd.hpp>

namespace sanguis::collision::impl::world::simple
{

using body_move_callback =
    fcppt::function<void(fcppt::reference<sanguis::collision::impl::world::simple::body>)>;

}

#endif
