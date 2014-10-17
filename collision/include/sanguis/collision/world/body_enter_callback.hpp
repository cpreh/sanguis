#ifndef SANGUIS_COLLISION_WORLD_BODY_ENTER_CALLBACK_HPP_INCLUDED
#define SANGUIS_COLLISION_WORLD_BODY_ENTER_CALLBACK_HPP_INCLUDED

#include <sanguis/collision/world/body_base_fwd.hpp>
#include <sanguis/collision/world/created_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <functional>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace collision
{
namespace world
{

typedef
std::function<
	void (
		sanguis::collision::world::body_base &,
		sanguis::collision::world::created
	)
>
body_enter_callback;

}
}
}

#endif
