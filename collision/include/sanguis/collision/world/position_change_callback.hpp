#ifndef SANGUIS_COLLISION_WORLD_POSITION_CHANGE_CALLBACK_HPP_INCLUDED
#define SANGUIS_COLLISION_WORLD_POSITION_CHANGE_CALLBACK_HPP_INCLUDED

#include <sanguis/collision/center_fwd.hpp>
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
		sanguis::collision::center
	)
>
position_change_callback;

}
}
}

#endif
