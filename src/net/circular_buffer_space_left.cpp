#include "circular_buffer_space_left.hpp"

sanguis::net::size_type
sanguis::net::circular_buffer_space_left(
	net::circular_buffer const &_buffer
)
{
	return
		_buffer.capacity()
		- _buffer.size();
}
