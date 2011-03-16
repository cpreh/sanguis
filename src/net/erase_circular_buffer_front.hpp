#ifndef SANGUIS_NET_ERASE_CIRCULAR_BUFFER_FRONT_HPP_INCLUDED
#define SANGUIS_NET_ERASE_CIRCULAR_BUFFER_FRONT_HPP_INCLUDED

#include "circular_buffer.hpp"
#include <cstddef>

namespace sanguis
{
namespace net
{

void
erase_circular_buffer_front(
	net::circular_buffer &,
	std::size_t size
);

}
}

#endif
