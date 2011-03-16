#include "erase_circular_buffer_front.hpp"

void
sanguis::net::erase_circular_buffer_front(
	net::circular_buffer &_buffer,
	std::size_t const _size
)
{
	_buffer.erase(
		_buffer.begin(),
		_buffer.begin()
		+
		static_cast<
			net::circular_buffer::iterator::difference_type
		>(
			_size
		)
	);
}
