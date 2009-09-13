#ifndef SANGUIS_SERVER_WORLD_RANDOM_HPP_INCLUDED
#define SANGUIS_SERVER_WORLD_RANDOM_HPP_INCLUDED

#include "object_auto_ptr.hpp"
#include "context_ptr.hpp"
#include <sge/collision/system_fwd.hpp>

namespace sanguis
{
namespace server
{
namespace world
{

object_auto_ptr
random(
	context_ptr,
	sge::collision::system_ptr
	// TODO: params
);

}
}
}

#endif
