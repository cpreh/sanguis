#ifndef SANGUIS_NET_SERVER_CONNECTION_CONTAINER_HPP_INCLUDED
#define SANGUIS_NET_SERVER_CONNECTION_CONTAINER_HPP_INCLUDED

#include <sanguis/net/server/connection_fwd.hpp>
#include <sanguis/net/id.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/ptr_container/ptr_map.hpp>
#include <fcppt/config/external_end.hpp>

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
