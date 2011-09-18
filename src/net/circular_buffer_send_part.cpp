#include <sanguis/net/circular_buffer_send_part.hpp>

sanguis::net::circular_buffer::const_array_range const
sanguis::net::circular_buffer_send_part(
	net::circular_buffer const &_buffer
)
{
	return
		_buffer.array_two().second == 0u
		?
			_buffer.array_one()
		:
			_buffer.array_two();
}
