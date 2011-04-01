#ifndef SANGUIS_SERVER_COLLISION_POSITION_CALLBACK_HPP_INCLUDED
#define SANGUIS_SERVER_COLLISION_POSITION_CALLBACK_HPP_INCLUDED

#include "../center.hpp"
#include <fcppt/function/object_fwd.hpp>

namespace sanguis
{
namespace server
{
namespace collision
{

typedef fcppt::function::object<
	void(
		server::center const &
	)
> position_callback;

}
}
}

#endif
