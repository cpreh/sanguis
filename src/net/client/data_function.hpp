#ifndef SANGUIS_NET_CLIENT_DATA_FUNCTION_HPP_INCLUDED
#define SANGUIS_NET_CLIENT_DATA_FUNCTION_HPP_INCLUDED

#include "../data_buffer.hpp"

namespace sanguis
{
namespace net
{
namespace client
{

typedef void
data_function(
	net::data_buffer const &
);

}
}
}

#endif