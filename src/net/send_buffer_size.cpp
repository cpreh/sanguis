#include <sanguis/net/send_buffer_size.hpp>
#include <alda/net/buffer/max_send_size.hpp>


alda::net::buffer::max_send_size const
sanguis::net::send_buffer_size()
{
	return
		alda::net::buffer::max_send_size(
			1024u * 64u
		);
}
