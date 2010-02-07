#ifndef SANGUIS_SERVER_WORLD_DEFERRED_ADD_QUEUE_HPP_INCLUDED
#define SANGUIS_SERVER_WORLD_DEFERRED_ADD_QUEUE_HPP_INCLUDED

#include "object_fwd.hpp"
#include <boost/ptr_container/ptr_deque.hpp>

namespace sanguis
{
namespace server
{
namespace world
{
namespace deferred_add
{

typedef boost::ptr_deque<
	object
> queue;

}
}
}
}

#endif
