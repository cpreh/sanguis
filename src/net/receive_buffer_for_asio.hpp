#ifndef SANGUIS_NET_RECEIVE_BUFFER_FOR_ASIO_HPP_INCLUDED
#define SANGUIS_NET_RECEIVE_BUFFER_FOR_ASIO_HPP_INCLUDED

#include "receive_buffer_fwd.hpp"
#include <boost/asio/buffer.hpp>

namespace sanguis
{
namespace net
{

boost::asio::mutable_buffers_1 const
receive_buffer_for_asio(
	net::receive_buffer &
);

}
}

#endif
