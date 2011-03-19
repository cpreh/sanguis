#ifndef SANGUIS_NET_DESERIALIZE_HPP_INCLUDED
#define SANGUIS_NET_DESERIALIZE_HPP_INCLUDED

#include "receive_buffer.hpp"
#include "../messages/auto_ptr.hpp"

namespace sanguis
{
namespace net
{

messages::auto_ptr
deserialize(
	net::receive_buffer &
);

}
}

#endif
