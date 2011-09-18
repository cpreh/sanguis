#ifndef SANGUIS_MESSAGES_SERIALIZATION_DISPATCH_MAP_HPP_INCLUDED
#define SANGUIS_MESSAGES_SERIALIZATION_DISPATCH_MAP_HPP_INCLUDED

#include <sanguis/messages/serialization/dispatcher_base_fwd.hpp>
#include <sanguis/messages/types/message.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/ptr_container/ptr_map.hpp>
#include <fcppt/config/external_end.hpp>

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
