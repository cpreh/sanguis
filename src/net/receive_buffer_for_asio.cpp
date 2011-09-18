#include <sanguis/net/receive_buffer_for_asio.hpp>
#include <sanguis/net/receive_buffer.hpp>
#include <sanguis/net/receive_buffer_part.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/asio/buffer.hpp>
#include <algorithm>
#include <fcppt/config/external_end.hpp>

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
			std::min(
				part.size(),
				static_cast<
					net::receive_buffer::size_type
				>(
					4096u
				)
			)
		);
}
