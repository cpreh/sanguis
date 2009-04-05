#ifndef SANGUIS_MESSAGES_SERIALIZATION_DISPATCH_MAP_HPP_INCLUDED
#define SANGUIS_MESSAGES_SERIALIZATION_DISPATCH_MAP_HPP_INCLUDED

#include "dispatcher_base_fwd.hpp"
#include "../types/message.hpp"
#include <boost/ptr_container/ptr_map.hpp>

namespace sanguis
{
namespace messages
{
namespace serialization
{

typedef boost::ptr_map<
	types::message::type,
	dispatcher_base
> dispatch_map;

}
}
}

#endif
