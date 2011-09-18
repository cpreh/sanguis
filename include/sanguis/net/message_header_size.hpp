#ifndef SANGUIS_NET_MESSAGE_HEADER_SIZE_HPP_INCLUDED
#define SANGUIS_NET_MESSAGE_HEADER_SIZE_HPP_INCLUDED

#include <sanguis/net/message_header.hpp>
#include <sanguis/net/size_type.hpp>

namespace sanguis
{
namespace net
{

// TODO: change this to an mpl::integral_c
net::size_type const
message_header_size(
	sizeof(net::message_header)
);

}
}

#endif
