#ifndef SANGUIS_SERVER_SPAWN_PICKUP_CALLBACK_HPP_INCLUDED
#define SANGUIS_SERVER_SPAWN_PICKUP_CALLBACK_HPP_INCLUDED

#include "pos_type.hpp"
#include <sge/function/object_fwd.hpp>

namespace sanguis
{
namespace server
{

typedef sge::function::object<
	void (
		pos_type const &
	)
> spawn_pickup_callback;

}
}

#endif
