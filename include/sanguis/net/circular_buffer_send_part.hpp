#ifndef SANGUIS_NET_CIRCULAR_BUFFER_SEND_PART_HPP_INCLUDED
#define SANGUIS_NET_CIRCULAR_BUFFER_SEND_PART_HPP_INCLUDED

#include <sanguis/net/circular_buffer.hpp>

namespace sanguis
{
namespace net
{

net::circular_buffer::const_array_range const
circular_buffer_send_part(
	net::circular_buffer const &
);

}
}

#endif
