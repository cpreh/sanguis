#include <sanguis/net/send_buffer_size.hpp>

sanguis::net::size_type
sanguis::net::send_buffer_size()
{
	return 1024 * 64;
}
