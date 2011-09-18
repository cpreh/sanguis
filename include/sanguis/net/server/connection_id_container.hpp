#ifndef SANGUIS_NET_SERVER_CONNECTION_ID_CONTAINER_HPP_INCLUDED
#define SANGUIS_NET_SERVER_CONNECTION_ID_CONTAINER_HPP_INCLUDED

#include <sanguis/net/server/connection_container.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/range/adaptor/map.hpp>
#include <fcppt/config/external_end.hpp>

namespace sanguis
{
namespace net
{
namespace server
{

typedef boost::select_first_range<
	net::server::connection_container
> connection_id_container;

}
}
}

#endif
