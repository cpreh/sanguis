#ifndef SANGUIS_NET_CLIENT_DATA_FUNCTION_HPP_INCLUDED
#define SANGUIS_NET_CLIENT_DATA_FUNCTION_HPP_INCLUDED

#include <sanguis/net/receive_buffer_fwd.hpp>

namespace sanguis
{
namespace net
{
namespace client
{

typedef void
data_function(
	net::receive_buffer &
);

}
}
}

#endif
