#ifndef SANGUIS_NET_ERASE_CIRCULAR_BUFFER_FRONT_HPP_INCLUDED
#define SANGUIS_NET_ERASE_CIRCULAR_BUFFER_FRONT_HPP_INCLUDED

#include <sanguis/net/circular_buffer.hpp>
#include <fcppt/config/external_begin.hpp>
#include <cstddef>
#include <fcppt/config/external_end.hpp>

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
