#include <alda/net/buffer/max_receive_size.hpp>
#include <sanguis/net/receive_buffer_size.hpp>


alda::net::buffer::max_receive_size const
sanguis::net::receive_buffer_size()
{
	return
		alda::net::buffer::max_receive_size(
			128u * 1024u
		);
}
