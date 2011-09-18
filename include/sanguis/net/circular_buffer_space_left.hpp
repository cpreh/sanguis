#ifndef SANGUIS_NET_CIRCULAR_BUFFER_SPACE_LEFT_HPP_INCLUDED
#define SANGUIS_NET_CIRCULAR_BUFFER_SPACE_LEFT_HPP_INCLUDED

#include <sanguis/net/circular_buffer.hpp>
#include <sanguis/net/size_type.hpp>

namespace sanguis
{
namespace net
{

net::size_type
circular_buffer_space_left(
	net::circular_buffer const &
);

}
}

#endif
