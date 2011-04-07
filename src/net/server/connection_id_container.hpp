#ifndef SANGUIS_NET_SERVER_CONNECTION_ID_CONTAINER_HPP_INCLUDED
#define SANGUIS_NET_SERVER_CONNECTION_ID_CONTAINER_HPP_INCLUDED

#include "connection_container.hpp"
#include <boost/range/adaptor/map.hpp>

namespace sanguis
{
namespace net
{
namespace server
{

typedef boost::select_first_range<
	server::connection_container
> connection_id_container;

}
}
}

#endif
