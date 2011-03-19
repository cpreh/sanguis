#include "receive_buffer_for_asio.hpp"
#include "receive_buffer.hpp"
#include "receive_buffer_part.hpp"
#include <boost/asio/buffer.hpp>
#include <cstddef>

boost::asio::mutable_buffers_1 const
sanguis::net::receive_buffer_for_asio(
	net::receive_buffer &_buffer
)
{
	net::receive_buffer_part const part(
		_buffer.next_receive_part()
	);

	return
		boost::asio::mutable_buffers_1(
			part.begin(),
			static_cast<
				std::size_t
			>(
				part.end() - part.end()
			)
		);
}
