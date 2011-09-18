#ifndef SANGUIS_NET_APPEND_TO_CIRCULAR_BUFFER_HPP_INCLUDED
#define SANGUIS_NET_APPEND_TO_CIRCULAR_BUFFER_HPP_INCLUDED

#include <sanguis/net/circular_buffer.hpp>
#include <sanguis/net/data_buffer.hpp>

namespace sanguis
{
namespace net
{

bool
append_to_circular_buffer(
	net::circular_buffer &,
	net::data_buffer const &
);

}
}

#endif
