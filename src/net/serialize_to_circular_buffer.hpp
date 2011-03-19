#ifndef SANGUIS_NET_SERIALIZE_TO_CIRCULAR_BUFFER_HPP_INCLUDED
#define SANGUIS_NET_SERIALIZE_TO_CIRCULAR_BUFFER_HPP_INCLUDED

#include "circular_buffer.hpp"
#include "../messages/auto_ptr.hpp"

namespace sanguis
{
namespace net
{

bool
serialize_to_circular_buffer(
	messages::auto_ptr,
	net::circular_buffer &
);

}
}

#endif
