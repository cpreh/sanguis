#ifndef SANGUIS_COLLISION_IMPL_WORLD_SIMPLE_BODY_CALLBACK_HPP_INCLUDED
#define SANGUIS_COLLISION_IMPL_WORLD_SIMPLE_BODY_CALLBACK_HPP_INCLUDED

#include <sanguis/collision/impl/world/simple/body_fwd.hpp>
#include <fcppt/function_impl.hpp>


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
fcppt::function<
	void (
		sanguis::collision::impl::world::simple::body &
	)
>
body_callback;

}
}
}
}
}

#endif
