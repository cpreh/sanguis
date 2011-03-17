#ifndef SANGUIS_NET_MESSAGE_HEADER_SIZE_HPP_INCLUDED
#define SANGUIS_NET_MESSAGE_HEADER_SIZE_HPP_INCLUDED

#include "message_header.hpp"
#include "size_type.hpp"

namespace sanguis
{
namespace net
{

net::size_type const
message_header_size(
	sizeof(net::message_header)
);

}
}

#endif
