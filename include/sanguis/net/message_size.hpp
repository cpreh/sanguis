#ifndef SANGUIS_NET_MESSAGE_SIZE_HPP_INCLUDED
#define SANGUIS_NET_MESSAGE_SIZE_HPP_INCLUDED

#include <sanguis/net/size_type.hpp>

namespace sanguis
{
namespace net
{

net::size_type
message_size(
	net::size_type body_size
);

}
}

#endif
