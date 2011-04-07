#ifndef SANGUIS_NET_SERVER_CONNECTION_CONTAINER_HPP_INCLUDED
#define SANGUIS_NET_SERVER_CONNECTION_CONTAINER_HPP_INCLUDED

#include "connection_fwd.hpp"
#include "../id.hpp"
#include <boost/ptr_container/ptr_map.hpp>

namespace sanguis
{
namespace net
{
namespace server
{

typedef boost::ptr_map<
	net::id,
	server::connection
> connection_container;

}
}
}

#endif
