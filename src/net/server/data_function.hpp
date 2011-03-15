#ifndef SANGUIS_NET_SERVER_DATA_FUNCTION_HPP_INCLUDED
#define SANGUIS_NET_SERVER_DATA_FUNCTION_HPP_INCLUDED

#include "../id.hpp"
#include "../data_buffer.hpp"

namespace sanguis
{
namespace net
{
namespace server
{

typedef void
disconnect_function(
	net::id,
	net::data_buffer const &
);

}
}
}

#endif
