#include <sanguis/net/receive_buffer_size.hpp>

sanguis::net::size_type
sanguis::net::receive_buffer_size()
{
	return 128 * 1024;
}
